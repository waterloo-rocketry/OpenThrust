import os
import sys
import threading


class GrabOutput:
    """
    Grab output from another stream
    """

    def __init__(self):
        self.origstream = sys.stdout
        self.origstreamfd = self.origstream.fileno()
        self.streamfd = None
        self.capturedOutput = ""
        self.pipe = os.pipe()
        self.workerThread = None

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop()

    def start(self):
        self.capturedOutput = ""
        self.streamfd = os.dup(self.origstreamfd)
        os.dup2(self.pipe[1], self.origstreamfd)
        os.close(self.pipe[1])
        self.workerThread = threading.Thread(target=self.readOutput)
        self.workerThread.start()

    def stop(self):
        self.origstream.write("\0")
        self.workerThread.join()
        os.close(self.pipe[0])
        os.dup2(self.streamfd, self.origstreamfd)
        os.close(self.streamfd)

    def readOutput(self):
        self.origstream.flush()
        while True:
            char = os.read(self.pipe[0], 1).decode(self.origstream.encoding)
            if '\0' in char:
                break
            self.capturedOutput += char
        return self.capturedOutput
