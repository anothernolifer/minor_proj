#pragma once
#include <cmath>

namespace Eloquent {
    namespace ML {
        namespace Port {
            class GaussianNBLight {
                public:
                    /**
                    * Predict class for features vector
                    * Correct Gaussian Naive Bayes log-likelihood:
                    * score_c = log(prior_c) - 0.5 * sum_i [ log(2*pi*var_ci) + (x_i - theta_ci)^2 / var_ci ]
                    */
                    int predict(float *x) {
                        float scores[5];

                        {
                            float theta[3] = {5.360189573f, 679.5444313f, -366.660545f};
                            float var[3] = {76.64538108f, 72650.54092f, 968808.8761f};
                            float logProb = -1.332753594f;
                            for (int i = 0; i < 3; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[0] = logProb;
                        }
                        {
                            float theta[3] = {15.28495575f, 1240.188938f, -36.3420354f};
                            float var[3] = {100.7179081f, 151343.5497f, 1206548.609f};
                            float logProb = -1.040933177f;
                            for (int i = 0; i < 3; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[1] = logProb;
                        }
                        {
                            float theta[3] = {21.4039466f, 1586.459083f, 642.3406849f};
                            float var[3] = {117.3103299f, 201583.037f, 1729489.857f};
                            float logProb = -1.312231033f;
                            for (int i = 0; i < 3; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[2] = logProb;
                        }
                        {
                            float theta[3] = {21.61296296f, 1586.962963f, 2228.505556f};
                            float var[3] = {100.4182548f, 153612.6648f, 559125.7384f};
                            float logProb = -2.47248413f;
                            for (int i = 0; i < 3; i++) {
                                float diff = x[i] - theta[i];
                                logProb -= 0.5f * (log(2.0f * M_PI * var[i]) + (diff * diff) / var[i]);
                            }
                            scores[3] = logProb;
                        }
                        {
                            float theta[3] = {25.46031746f, 1784.21164f, 3050.740741f};
                            float var[3] = {73.478118f, 72146.68755f, 213832.4164f};
                            float logProb = -3.522306254f;
                            for (int i = 0; i < 3; i++) {
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