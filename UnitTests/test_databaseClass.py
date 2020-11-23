import pytest

from constants import NIST_PATH
import databaseClass as db


class TestHelpers:
    def test_calcQuality(self):
        x = db.calcQuality(2.5, 2, 3)
        assert x == pytest.approx(0.96)


class TestDB:
    def test_grabPropsValidTemp(self):
        database = db.DataBase(NIST_PATH)
        result = database.grabProps(5, T=273)
        assert result["T"] == 273
        assert result["P"] == pytest.approx(451.08, rel=1e-4)
        assert result["rho_L_NIST"] == pytest.approx(907.827, rel=1e-4)
        assert result["h_L_NIST"] == pytest.approx(165.2363, rel=1e-4)
        assert result["s_L_NIST"] == pytest.approx(0.7137, rel=1e-4)
        assert result["rho_V_NIST"] == pytest.approx(84.7932, rel=1e-4)
        assert result["h_V_NIST"] == pytest.approx(398.3009, rel=1e-4)
        assert result["s_V_NIST"] == pytest.approx(1.5674, rel=1e-4)
        assert result["X"] == pytest.approx(3.7412, rel=1e-4)
        assert result["h"] == pytest.approx(1037.1684, rel=1e-4)
        assert result["s"] == pytest.approx(3.9074, rel=1e-4)

    def test_grabPropsValidPressure(self):
        database = db.DataBase(NIST_PATH)
        result = database.grabProps(5, P=451.08)
        assert result["T"] == pytest.approx(273, rel=1e-4)
        assert result["P"] == 451.08
        assert result["rho_L_NIST"] == pytest.approx(907.827, rel=1e-4)
        assert result["h_L_NIST"] == pytest.approx(165.2363, rel=1e-4)
        assert result["s_L_NIST"] == pytest.approx(0.7137, rel=1e-4)
        assert result["rho_V_NIST"] == pytest.approx(84.7932, rel=1e-4)
        assert result["h_V_NIST"] == pytest.approx(398.3009, rel=1e-4)
        assert result["s_V_NIST"] == pytest.approx(1.5674, rel=1e-4)
        assert result["X"] == pytest.approx(3.7412, rel=1e-4)
        assert result["h"] == pytest.approx(1037.1684, rel=1e-4)
        assert result["s"] == pytest.approx(3.9074, rel=1e-4)

    def test_grabPropsInvalidTemp(self):
        database = db.DataBase(NIST_PATH)
        assert pytest.raises(ValueError, database.grabProps, 5, 0, None)

    def test_grabPropsInvalidPressure(self):
        database = db.DataBase(NIST_PATH)
        assert pytest.raises(ValueError, database.grabProps, 5, None, 0)

    def test_grabPropsInvalidRho(self):
        database = db.DataBase(NIST_PATH)
        assert pytest.raises(ValueError, database.grabProps, 0, 273, None)

    def test_grabPropsNoTempOrPressure(self):
        database = db.DataBase(NIST_PATH)
        assert pytest.raises(ValueError, database.grabProps, 5, None, None)

    def test_grabPropsTempAndPressure(self):
        database = db.DataBase(NIST_PATH)
        result = database.grabProps(5, T=273, P=1)
        assert result["T"] == 273
        assert result["P"] == pytest.approx(451.08, rel=1e-4)
        assert result["rho_L_NIST"] == pytest.approx(907.827, rel=1e-4)
        assert result["h_L_NIST"] == pytest.approx(165.2363, rel=1e-4)
        assert result["s_L_NIST"] == pytest.approx(0.7137, rel=1e-4)
        assert result["rho_V_NIST"] == pytest.approx(84.7932, rel=1e-4)
        assert result["h_V_NIST"] == pytest.approx(398.3009, rel=1e-4)
        assert result["s_V_NIST"] == pytest.approx(1.5674, rel=1e-4)
        assert result["X"] == pytest.approx(3.7412, rel=1e-4)
        assert result["h"] == pytest.approx(1037.1684, rel=1e-4)
        assert result["s"] == pytest.approx(3.9074, rel=1e-4)
