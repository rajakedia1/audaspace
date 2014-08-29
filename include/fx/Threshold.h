/*******************************************************************************
 * Copyright 2009-2013 Jörg Müller
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#pragma once

#include "fx/Effect.h"

AUD_NAMESPACE_BEGIN

class CallbackIIRFilterReader;

/**
 * This sound Transforms any signal to a square signal by thresholding.
 */
class Threshold : public Effect
{
private:
	/**
	 * The threshold.
	 */
	const float m_threshold;

	// delete copy constructor and operator=
	Threshold(const Threshold&) = delete;
	Threshold& operator=(const Threshold&) = delete;

public:
	/**
	 * Creates a new threshold sound.
	 * \param sound The input sound.
	 * \param threshold The threshold.
	 */
	Threshold(std::shared_ptr<ISound> sound, float threshold = 0.0f);

	/**
	 * Returns the threshold.
	 */
	float getThreshold() const;

	virtual std::shared_ptr<IReader> createReader();

	static sample_t thresholdFilter(CallbackIIRFilterReader* reader, float* threshold);
	static void endThresholdFilter(float* threshold);
};

AUD_NAMESPACE_END