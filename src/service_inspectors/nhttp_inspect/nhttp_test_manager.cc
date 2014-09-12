/****************************************************************************
 *
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2003-2013 Sourcefire, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.  You may not use, modify or
 * distribute this program under any other version of the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 ****************************************************************************/

//
//  @author     Tom Peters <thopeter@cisco.com>
//
//  @brief      Control NHttpInspect test tools
//

#include <stdexcept>
#include "nhttp_test_manager.h"
#include "nhttp_test_input.h"

bool NHttpTestManager::test_input = false;
NHttpTestInput NHttpTestManager::test_input_source("nhttp_test_msgs.txt");
const char* NHttpTestManager::test_output_prefix = "nhttpresults/testcase";

void NHttpTestManager::update_test_number(int64_t new_test_number) {
    if (new_test_number != test_number) {
        if (test_out != nullptr) fclose (test_out);
        test_number = new_test_number;
        char file_name[100];
        snprintf(file_name, sizeof(file_name), "%s%" PRIi64 ".txt", test_output_prefix, test_number);
        if ((test_out = fopen(file_name, "w+")) == nullptr) throw std::runtime_error("Cannot open test output file");
    }
}

