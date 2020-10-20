import pytest
import configReader
from dataclasses import dataclass


@dataclass
class MockModel:
    V: float = 0
    nozThroatArea: float = 0
    nozExitArea: float = 0
    Ac: float = 0
    Cd: float = 0
    OF: float = 0
    rampUpTime: float = 0
    rampDownTime: float = 0
    dt: float = 0


class TestConfig:
    def test_configParse(self):
        testStruct = MockModel()
        configReader.ReadSettings(testStruct, r"UnitTests\testConfig.cfg")

        assert testStruct.V == pytest.approx(6.9 / 1e3)
        assert testStruct.nozThroatArea == pytest.approx(3.82646 / 1e4)
        assert testStruct.nozExitArea == pytest.approx(18.1001 / 1e4)
        assert testStruct.Ac == pytest.approx(0.2826 / 1e4)
        assert testStruct.Cd == pytest.approx(0.8)
        assert testStruct.OF == pytest.approx(2.1)
        assert testStruct.rampUpTime == pytest.approx(4.0)
        assert testStruct.rampDownTime == pytest.approx(6.0)
        assert testStruct.dt == pytest.approx(0.05)
