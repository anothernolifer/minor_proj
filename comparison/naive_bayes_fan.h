#pragma once
#include <cmath>

namespace Eloquent {
    namespace ML {
        namespace Port {
            class GaussianNBFan {
                public:
                    /**
                    * Predict class for features vector
                    * Correct Gaussian Naive Bayes log-likelihood:
                    * score_c = log(prior_c) - 0.5 * sum_i [ log(2*pi*var_ci) + (x_i - theta_ci)^2 / var_ci ]
                    */
                    int predict(float *x) {
                        float scores[5];

                        {
                            float theta[4] = {1.439849624f, 473.4398496f, 30.76315789f, 62.1518797f};
                            float var[4] = {8.958359734f, 49869.00347f, 119.2335528f, 111.3280833f};
                            float logProb = -3.180556961f;
                            for (int i = 0; i < 4; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[0] = logProb;
                        }
                        {
                            float theta[4] = {9.35381914f, 901.14223f, 26.37243196f, 59.22080773f};
                            float var[4] = {44.84868028f, 167601.1319f, 47.94225664f, 71.04685936f};
                            float logProb = -1.726147306f;
                            for (int i = 0; i < 4; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[1] = logProb;
                        }
                        {
                            float theta[4] = {14.4756141f, 1192.237095f, 33.67027412f, 64.3741189f};
                            float var[4] = {66.26327795f, 231395.5782f, 60.6275529f, 78.56497567f};
                            float logProb = -0.8234694422f;
                            for (int i = 0; i < 4; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[2] = logProb;
                        }
                        {
                            float theta[4] = {19.79054842f, 1493.53734f, 40.15350058f, 68.58926488f};
                            float var[4] = {55.63983558f, 198354.5758f, 54.55989224f, 72.48038144f};
                            float logProb = -1.31746817f;
                            for (int i = 0; i < 4; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[3] = logProb;
                        }
                        {
                            float theta[4] = {24.01271186f, 1729.427966f, 46.8565678f, 73.65614407f};
                            float var[4] = {27.11894632f, 117254.0631f, 39.83080207f, 63.7258922f};
                            float logProb = -2.607074284f;
                            for (int i = 0; i < 4; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[4] = logProb;
                        }

                        int bestClass = 0;
                        float bestScore = scores[0];
                        for (int i = 1; i < 5; i++) {
                            if (scores[i] > bestScore) {
                                bestScore = scores[i];
                                bestClass = i;
                            }
                        }
                        return bestClass;
                    }
            };
        }
    }
}