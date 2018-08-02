/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "execution_barrier.h"

namespace bluetooth {

namespace common {

void ExecutionBarrier::WaitForExecution() {
  std::unique_lock<std::mutex> lock(execution_mutex_);
  while (!finished_) {
    execution_cv_.wait(lock);
  }
}

void ExecutionBarrier::NotifyFinished() {
  std::unique_lock<std::mutex> lock(execution_mutex_);
  finished_ = true;
  execution_cv_.notify_all();
}

}  // namespace common

}  // namespace bluetooth