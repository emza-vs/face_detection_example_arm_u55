/*
 * Copyright (c) 2022 Arm Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef DETECTOR_POST_PROCESSING_HPP
#define DETECTOR_POST_PROCESSING_HPP

#include "UseCaseCommonUtils.hpp"
#include "DetectionResult.hpp"

#define DISPLAY_RGB_IMAGE (1)

#define INPUT_IMAGE_WIDTH 192
#define INPUT_IMAGE_HEIGHT 192

#define ORIGINAL_IMAGE_WIDTH 192
#define ORIGINAL_IMAGE_HEIGHT 192

#if DISPLAY_RGB_IMAGE
#define FORMAT_MULTIPLY_FACTOR 3
#else
#define FORMAT_MULTIPLY_FACTOR 1
#endif /* DISPLAY_RGB_IMAGE */

void runPostProcessing(uint8_t *img_in,TfLiteTensor* model_output[2],std::vector<arm::app::DetectionResult> & results_out);

void draw_box_on_image(uint8_t *img_in,int im_w,int im_h,int bx,int by,int bw,int bh);
void rgb_to_grayscale(const uint8_t *rgb,uint8_t *gray, int im_w,int im_h);

#endif /* DETECTOR_POST_PROCESSING_HPP */
