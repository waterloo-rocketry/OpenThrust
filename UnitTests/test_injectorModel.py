from Models.injectorModel import *

from dataclasses import dataclass

import pytest


@dataclass
class MockModel:
    P1: float = 0
    P2: float = 0
    Pv1: float = 0
    rho1: float = 0
    rho2: float = 0
    h1: float = 0
    h2: float = 0


class TestDyer:
    def test_goodInput(self):
        testStruct = MockModel(451.08, 14.7, 451.08, 144.93, 273.0, 291.63, 221.07)
        injector = DyerModel(testStruct, 2.826*10**-5, 0.8)
        result = injector.getMassFlowRate()
        # Compare to expected result as calculated separately
        assert result == pytest.approx(0.37048, 5e-5)

    def test_h1LTh2(self):
        # Case where h1 < h2, mdot_HEM should be 0
        testStruct = MockModel(451.08, 14.7, 451.08, 144.93, 273.0, 221.07, 291.63)
        injector = DyerModel(testStruct, 2.826*10**-5, 0.8)
        injector.getMassFlowRate()
        assert injector.mdot_HEM == 0

    def test_invalPError(self):
        # P1 < P2
        testStruct = MockModel(14.7, 451.08, 451.08, 144.93, 273.0, 291.63, 221.07)
        injector = DyerModel(testStruct, 2.826*10**-5, 0.8)
        assert pytest.raises(ValueError, injector.getMassFlowRate)

        # Pv1 == P2
        testStruct.P1 = 451.08
        testStruct.P2 = testStruct.Pv1 = 300
        assert pytest.raises(ValueError, injector.getMassFlowRate)

        # Pv1 < P2
        testStruct.Pv1 = 200
        assert pytest.raises(ValueError, injector.getMassFlowRate)
