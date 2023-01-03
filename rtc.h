 1 /* mbed Microcontroller Library
    2  * Copyright (c) 2006-2019 ARM Limited
    3  * SPDX-License-Identifier: Apache-2.0
    4  *
    5  * Licensed under the Apache License, Version 2.0 (the "License");
    6  * you may not use this file except in compliance with the License.
    7  * You may obtain a copy of the License at
    8  *
    9  *     http://www.apache.org/licenses/LICENSE-2.0
   10  *
   11  * Unless required by applicable law or agreed to in writing, software
   12  * distributed under the License is distributed on an "AS IS" BASIS,
   13  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   14  * See the License for the specific language governing permissions and
   15  * limitations under the License.
   16  */
   17 
   18 #ifndef __MBED_RTC_TIME_H__
   19 #define __MBED_RTC_TIME_H__
   20 
   21 #include <time.h>
   22 
   23 #ifdef __cplusplus
   24 extern "C" {
   25 #endif
   26 
   27 /** \addtogroup platform-public-api */
   28 /** @{*/
   29 
   30 /**
   31  * \defgroup platform_rtc_time rtc_time functions
   32  * @{
   33  */
   34 
   35 /* Timeval definition for non GCC_ARM toolchains,
   36  * Note: The GNU libc defines _TIMEVAL_DEFINED and the newlib defines __timeval_defined,
   37  * thus the double-check and double-define
   38  */
   39 #if !defined(__timeval_defined) && !defined(_TIMEVAL_DEFINED)
   40 #define __timeval_defined 1
   41 #define _TIMEVAL_DEFINED
   42 struct timeval {
   43     time_t tv_sec;
   44     int32_t tv_usec;
   45 };
   46 #endif
   47 
   48 /** Implementation of the C time.h functions
   49  *
   50  * Provides mechanisms to set and read the current time, based
   51  * on the microcontroller Real-Time Clock (RTC), plus some
   52  * standard C manipulation and formatting functions.
   53  *
   54  * Example:
   55  * @code
   56  * #include "mbed.h"
   57  *
   58  * int main() {
   59  *     set_time(1256729737);  // Set RTC time to Wed, 28 Oct 2009 11:35:37
   60  *
   61  *     while (true) {
   62  *         time_t seconds = time(NULL);
   63  *
   64  *         printf("Time as seconds since January 1, 1970 = %u\n", (unsigned int)seconds);
   65  *
   66  *         printf("Time as a basic string = %s", ctime(&seconds));
   67  *
   68  *         char buffer[32];
   69  *         strftime(buffer, 32, "%I:%M %p\n", localtime(&seconds));
   70  *         printf("Time as a custom formatted string = %s", buffer);
   71  *
   72  *         ThisThread::sleep_for(1000);
   73  *     }
   74  * }
   75  * @endcode
   76  */
   77 
   78 /** Set the current time
   79  *
   80  * Initializes and sets the time of the microcontroller Real-Time Clock (RTC)
   81  * to the time represented by the number of seconds since January 1, 1970
   82  * (the UNIX timestamp).
   83  *
   84  * @param t Number of seconds since January 1, 1970 (the UNIX timestamp)
   85  *
   86  * @note Synchronization level: Thread safe
   87  *
   88  * Example:
   89  * @code
   90  * #include "mbed.h"
   91  *
   92  * int main() {
   93  *     set_time(1256729737); // Set time to Wed, 28 Oct 2009 11:35:37
   94  * }
   95  * @endcode
   96  */
   97 void set_time(time_t t);
   98 
   99 /** Attach an external RTC to be used for the C time functions
  100  *
  101  * @note Synchronization level: Thread safe
  102  *
  103  * @param read_rtc pointer to function which returns current UNIX timestamp
  104  * @param write_rtc pointer to function which sets current UNIX timestamp, can be NULL
  105  * @param init_rtc pointer to function which initializes RTC, can be NULL
  106  * @param isenabled_rtc pointer to function which returns if the RTC is enabled, can be NULL
  107  */
  108 void attach_rtc(time_t (*read_rtc)(void), void (*write_rtc)(time_t), void (*init_rtc)(void), int (*isenabled_rtc)(void));
  109 
  110 /** Standard lib retarget, get time since Epoch
  111  *
  112  * @param tv    Structure containing time_t seconds and useconds_t microseconds. Due to
  113  *              separate target specific RTC implementations only the seconds component is used.
  114  * @param tz    DEPRECATED IN THE STANDARD: This parameter is left in for legacy code. It is
  115  *              not used.
  116  * @return      0 on success, -1 on a failure.
  117  * @note Synchronization level: Thread safe
  118  *
  119  */
  120 int gettimeofday(struct timeval *tv, void *tz);
  121 
  122 /** Standard lib retarget, set time since Epoch
  123  *
  124  * @param tv    Structure containing time_t seconds and useconds_t microseconds. Due to
  125  *              separate target specific RTC implementations only the seconds component is used.
  126  * @param tz    DEPRECATED IN THE STANDARD: This parameter is left in for legacy code. It is
  127  *              not used.
  128  * @return      Time in seconds on success, -1 on a failure.
  129  * @note Synchronization level: Thread safe
  130  *
  131  */
  132 int settimeofday(const struct timeval *tv, const struct timezone *tz);
  133 
  134 #ifdef __cplusplus
  135 }
  136 #endif
  137 
  138 /** @}*/
  139 /** @}*/
  140 
  141 #endif /* __MBED_RTC_TIME_H__ */
