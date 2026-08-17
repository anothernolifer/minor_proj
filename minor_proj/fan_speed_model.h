#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTreeFan {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[1] <= 1905.5) {
                            if (x[1] <= 1220.5) {
                                if (x[0] <= 0.5) {
                                    if (x[2] <= 24.800000190734863) {
                                        if (x[2] <= 23.75) {
                                            return 0;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }

                                    else {
                                        return 0;
                                    }
                                }

                                else {
                                    if (x[2] <= 39.45000076293945) {
                                        if (x[1] <= 557.5) {
                                            if (x[2] <= 30.949999809265137) {
                                                if (x[2] <= 25.449999809265137) {
                                                    if (x[0] <= 1.5) {
                                                        return 0;
                                                    }

                                                    else {
                                                        if (x[3] <= 62.19999885559082) {
                                                            return 0;
                                                        }

                                                        else {
                                                            return 0;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[3] <= 65.35000228881836) {
                                                        if (x[3] <= 53.05000114440918) {
                                                            return 0;
                                                        }

                                                        else {
                                                            return 0;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 384.5) {
                                                            return 0;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[1] <= 345.5) {
                                                    return 1;
                                                }

                                                else {
                                                    if (x[3] <= 56.75) {
                                                        if (x[3] <= 49.25) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[3] <= 61.85000038146973) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[2] <= 19.550000190734863) {
                                                if (x[0] <= 3.5) {
                                                    if (x[3] <= 60.89999961853027) {
                                                        return 0;
                                                    }

                                                    else {
                                                        if (x[3] <= 74.54999923706055) {
                                                            return 0;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[1] <= 974.5) {
                                                        if (x[3] <= 59.29999923706055) {
                                                            return 0;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[3] <= 61.60000038146973) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[1] <= 978.5) {
                                                    if (x[2] <= 27.65000057220459) {
                                                        if (x[3] <= 57.44999885559082) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[3] <= 49.85000038146973) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 33.45000076293945) {
                                                        if (x[3] <= 72.9000015258789) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[3] <= 56.89999961853027) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[1] <= 889.5) {
                                            if (x[0] <= 2.5) {
                                                if (x[3] <= 68.04999923706055) {
                                                    if (x[1] <= 682.5) {
                                                        if (x[3] <= 48.35000038146973) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[3] <= 62.60000038146973) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 45.25) {
                                                        return 1;
                                                    }

                                                    else {
                                                        if (x[1] <= 532.5) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[2] <= 52.54999923706055) {
                                                    if (x[3] <= 60.14999961853027) {
                                                        if (x[1] <= 855.0) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 743.0) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[2] <= 45.35000038146973) {
                                                if (x[1] <= 988.0) {
                                                    if (x[3] <= 60.30000114440918) {
                                                        return 1;
                                                    }

                                                    else {
                                                        if (x[0] <= 4.5) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[3] <= 56.75) {
                                                        if (x[1] <= 1054.0) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 1028.5) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[1] <= 970.5) {
                                                    if (x[2] <= 47.89999961853027) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[2] <= 25.050000190734863) {
                                    if (x[1] <= 1524.0) {
                                        if (x[3] <= 65.70000076293945) {
                                            if (x[3] <= 56.25) {
                                                return 1;
                                            }

                                            else {
                                                if (x[2] <= 18.050000190734863) {
                                                    if (x[2] <= 14.549999713897705) {
                                                        return 1;
                                                    }

                                                    else {
                                                        return 1;
                                                    }
                                                }

                                                else {
                                                    if (x[0] <= 8.5) {
                                                        if (x[1] <= 1471.5) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[1] <= 1352.0) {
                                                if (x[0] <= 6.5) {
                                                    return 1;
                                                }

                                                else {
                                                    if (x[1] <= 1284.0) {
                                                        return 1;
                                                    }

                                                    else {
                                                        return 1;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[0] <= 7.5) {
                                                    return 1;
                                                }

                                                else {
                                                    if (x[3] <= 72.54999923706055) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[3] <= 56.25) {
                                            if (x[2] <= 17.65000057220459) {
                                                return 1;
                                            }

                                            else {
                                                if (x[1] <= 1722.0) {
                                                    return 1;
                                                }

                                                else {
                                                    if (x[1] <= 1817.0) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[2] <= 13.200000286102295) {
                                                if (x[0] <= 10.5) {
                                                    return 1;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                if (x[1] <= 1730.0) {
                                                    if (x[2] <= 22.0) {
                                                        if (x[3] <= 69.25) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 1682.5) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[2] <= 41.85000038146973) {
                                        if (x[1] <= 1433.5) {
                                            if (x[3] <= 55.79999923706055) {
                                                if (x[2] <= 38.30000114440918) {
                                                    if (x[3] <= 47.80000114440918) {
                                                        if (x[1] <= 1378.0) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 1301.5) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[3] <= 49.54999923706055) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[1] <= 1270.0) {
                                                    if (x[2] <= 36.20000076293945) {
                                                        if (x[3] <= 66.6500015258789) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 30.15000057220459) {
                                                        if (x[3] <= 67.60000228881836) {
                                                            return 1;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 35.89999961853027) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[3] <= 72.95000076293945) {
                                                if (x[0] <= 12.5) {
                                                    if (x[2] <= 36.45000076293945) {
                                                        if (x[2] <= 26.25) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 1793.5) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 33.79999923706055) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[2] <= 34.30000114440918) {
                                                    if (x[1] <= 1809.5) {
                                                        if (x[3] <= 74.35000228881836) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 30.149999618530273) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[1] <= 1698.0) {
                                                        if (x[2] <= 39.29999923706055) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 1795.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[1] <= 1638.0) {
                                            if (x[2] <= 51.30000114440918) {
                                                if (x[1] <= 1526.5) {
                                                    if (x[2] <= 48.64999961853027) {
                                                        return 2;
                                                    }

                                                    else {
                                                        if (x[1] <= 1472.0) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[3] <= 72.19999694824219) {
                                                        if (x[2] <= 48.04999923706055) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[1] <= 1469.5) {
                                                    if (x[3] <= 65.4000015258789) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[0] <= 9.5) {
                                                if (x[2] <= 48.75) {
                                                    if (x[3] <= 63.35000038146973) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                if (x[3] <= 61.25) {
                                                    if (x[2] <= 45.39999961853027) {
                                                        if (x[1] <= 1836.0) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 1784.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[0] <= 11.5) {
                                                        if (x[3] <= 73.14999771118164) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 2668.5) {
                                if (x[2] <= 28.15000057220459) {
                                    if (x[1] <= 2366.5) {
                                        if (x[1] <= 2130.5) {
                                            if (x[3] <= 65.25) {
                                                if (x[1] <= 2078.5) {
                                                    if (x[3] <= 47.80000114440918) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 24.699999809265137) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[2] <= 25.84999942779541) {
                                                    if (x[0] <= 13.5) {
                                                        if (x[2] <= 22.5) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[2] <= 25.65000057220459) {
                                                if (x[3] <= 66.20000076293945) {
                                                    if (x[1] <= 2299.5) {
                                                        if (x[2] <= 21.699999809265137) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 18.899999618530273) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 18.550000190734863) {
                                                        return 2;
                                                    }

                                                    else {
                                                        if (x[1] <= 2264.0) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[1] <= 2228.0) {
                                                    if (x[3] <= 69.20000076293945) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    if (x[0] <= 14.5) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[2] <= 17.449999809265137) {
                                            if (x[0] <= 16.5) {
                                                if (x[3] <= 63.44999885559082) {
                                                    return 2;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                if (x[2] <= 14.050000190734863) {
                                                    return 3;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[0] <= 14.5) {
                                                if (x[3] <= 67.0) {
                                                    return 2;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                if (x[3] <= 49.60000038146973) {
                                                    return 3;
                                                }

                                                else {
                                                    if (x[2] <= 19.75) {
                                                        if (x[3] <= 65.54999923706055) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 2399.0) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[1] <= 2120.5) {
                                        if (x[2] <= 36.35000038146973) {
                                            if (x[3] <= 57.85000038146973) {
                                                if (x[1] <= 2079.5) {
                                                    if (x[1] <= 2026.0) {
                                                        return 2;
                                                    }

                                                    else {
                                                        if (x[1] <= 2046.5) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                if (x[2] <= 31.34999942779541) {
                                                    if (x[1] <= 2105.5) {
                                                        if (x[3] <= 65.44999694824219) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 2;
                                                        }
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    if (x[0] <= 12.5) {
                                                        if (x[3] <= 72.85000228881836) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 33.69999885559082) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[3] <= 53.04999923706055) {
                                                if (x[2] <= 42.10000038146973) {
                                                    return 2;
                                                }

                                                else {
                                                    if (x[1] <= 1970.5) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[2] <= 38.35000038146973) {
                                                    if (x[1] <= 1951.0) {
                                                        return 2;
                                                    }

                                                    else {
                                                        if (x[3] <= 61.94999885559082) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 42.54999923706055) {
                                                        if (x[2] <= 40.25) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 2096.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[2] <= 50.14999961853027) {
                                            if (x[0] <= 17.5) {
                                                if (x[3] <= 49.64999961853027) {
                                                    if (x[1] <= 2289.5) {
                                                        if (x[2] <= 40.54999923706055) {
                                                            return 2;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 33.19999885559082) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 41.45000076293945) {
                                                        if (x[0] <= 13.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 2442.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[3] <= 70.60000228881836) {
                                                    if (x[3] <= 62.45000076293945) {
                                                        if (x[1] <= 2631.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 34.25) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 38.95000076293945) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 4;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[1] <= 2389.5) {
                                                if (x[2] <= 52.75) {
                                                    return 3;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                if (x[3] <= 56.849998474121094) {
                                                    return 4;
                                                }

                                                else {
                                                    return 4;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[2] <= 33.75) {
                                    if (x[2] <= 27.25) {
                                        if (x[0] <= 16.5) {
                                            return 3;
                                        }

                                        else {
                                            if (x[3] <= 81.20000076293945) {
                                                if (x[1] <= 2917.5) {
                                                    if (x[3] <= 46.75) {
                                                        return 3;
                                                    }

                                                    else {
                                                        if (x[2] <= 26.050000190734863) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }

                                                else {
                                                    if (x[3] <= 67.75) {
                                                        if (x[3] <= 57.80000114440918) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 22.65000057220459) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                return 3;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[3] <= 69.70000076293945) {
                                            if (x[1] <= 2992.5) {
                                                if (x[3] <= 58.64999961853027) {
                                                    if (x[1] <= 2726.0) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    if (x[1] <= 2843.5) {
                                                        if (x[3] <= 67.6500015258789) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 2918.5) {
                                                            return 4;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[3] <= 60.04999923706055) {
                                                    if (x[2] <= 31.5) {
                                                        if (x[3] <= 53.89999961853027) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    if (x[2] <= 31.0) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 4;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[1] <= 2841.5) {
                                                if (x[1] <= 2783.5) {
                                                    return 3;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                if (x[2] <= 28.600000381469727) {
                                                    return 4;
                                                }

                                                else {
                                                    if (x[0] <= 19.5) {
                                                        return 4;
                                                    }

                                                    else {
                                                        return 4;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[2] <= 39.64999961853027) {
                                        if (x[3] <= 63.64999961853027) {
                                            if (x[1] <= 2966.5) {
                                                if (x[2] <= 34.95000076293945) {
                                                    return 3;
                                                }

                                                else {
                                                    if (x[3] <= 52.5) {
                                                        if (x[2] <= 37.95000076293945) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        if (x[0] <= 18.5) {
                                                            return 3;
                                                        }

                                                        else {
                                                            return 4;
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[0] <= 19.5) {
                                                    return 4;
                                                }

                                                else {
                                                    if (x[3] <= 55.14999961853027) {
                                                        return 4;
                                                    }

                                                    else {
                                                        return 4;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[1] <= 2804.5) {
                                                if (x[1] <= 2764.0) {
                                                    if (x[1] <= 2739.5) {
                                                        if (x[3] <= 70.95000076293945) {
                                                            return 4;
                                                        }

                                                        else {
                                                            return 3;
                                                        }
                                                    }

                                                    else {
                                                        return 4;
                                                    }
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                if (x[3] <= 66.3499984741211) {
                                                    return 4;
                                                }

                                                else {
                                                    return 4;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[2] <= 43.04999923706055) {
                                            if (x[0] <= 17.5) {
                                                return 3;
                                            }

                                            else {
                                                if (x[1] <= 2760.5) {
                                                    return 4;
                                                }

                                                else {
                                                    if (x[3] <= 60.55000114440918) {
                                                        if (x[3] <= 57.64999961853027) {
                                                            return 4;
                                                        }

                                                        else {
                                                            return 4;
                                                        }
                                                    }

                                                    else {
                                                        if (x[1] <= 2840.5) {
                                                            return 4;
                                                        }

                                                        else {
                                                            return 4;
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[0] <= 17.5) {
                                                if (x[2] <= 45.35000038146973) {
                                                    return 4;
                                                }

                                                else {
                                                    return 4;
                                                }
                                            }

                                            else {
                                                if (x[1] <= 2718.5) {
                                                    return 4;
                                                }

                                                else {
                                                    return 4;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "0";
                            case 1:
                            return "1";
                            case 2:
                            return "2";
                            case 3:
                            return "3";
                            case 4:
                            return "4";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                };
            }
        }
    }