import os
import sys
import threading


class GrabOutput:
    """
    Grab output from another stream. Can either be used with a 'with' block or by calling the start() and stop()
    methods manually.

    While active, all stdout is redirected.

    See https://stackoverflow.com/questions/24277488/in-python-how-to-capture-the-stdout-from-a-c-shared-library-to-a-variable
    """

    def __init__(self):
        # Save the information for stdout so that it can be restored later
        self.origstream = sys.stdout
        self.origstreamfd = self.origstream.fileno()

        # Initialize other variables and create the os pipe where the output will be redirected
        self.streamfd = None
        self.capturedOutput = ""
        self.pipe = os.pipe()
        self.workerThread = None

    def __enter__(self):
        # Upon entering a 'with' block using the object, call the start() method
        self.start()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        # Upon exiting a 'with' block using the object, call the stop() method
        self.stop()

    def start(self):
        # Clear capturedOutput so that new output can be written into the empty string
        self.capturedOutput = ""
        # Duplicate the file descriptor of stdout to be restored later
        self.streamfd = os.dup(self.origstreamfd)
        # Duplicate the file descriptor of the 'write' end of the pipe created at initialization to stdout, closing the
        # original stdout
        os.dup2(self.pipe[1], self.origstreamfd)
        os.close(self.pipe[1])
        # Start a background thread that will read everything written to the pipe
        self.workerThread = threading.Thread(target=self.readOutput)
        self.workerThread.start()

    def stop(self):
        # Write the chosen end character to the stream to stop the background thread even if it hasn't reached the end,
        # then wait for the thread to finish
        self.origstream.write("\0")
        self.workerThread.join()
        # Close the 'read' end of the pipe and restore the correct file number for stdout
        os.close(self.pipe[0])
        os.dup2(self.streamfd, self.origstreamfd)
        os.close(self.streamfd)

    def readOutput(self):
        # Get all contents from the pipe and read them
        self.origstream.flush()
        while True:
            # Decode the character according to the encoding of the stream
            char = os.read(self.pipe[0], 1).decode(self.origstream.encoding)
            # \0 chosen as the break character, indicates the effective end of the stream (either forced by stop or
            # from the redirected output)
            if '\0' in char:
                break
            # Record the added character in CapturedOutput
            self.capturedOutput += char
        # Return the captured output
        return self.capturedOutput
