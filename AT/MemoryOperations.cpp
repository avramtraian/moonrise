/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#include "AT/MemoryOperations.h"

namespace AT {

void copy_memory(void* destination_buffer, const void* source_buffer, usize byte_count)
{
    WriteonlyBytes destination = reinterpret_cast<WriteonlyBytes>(destination_buffer);
    ReadonlyBytes source = reinterpret_cast<ReadonlyBytes>(source_buffer);

    for (usize offset = 0; offset < byte_count; ++offset) {
        destination[offset] = source[offset];
    }
}

void set_memory(void* destination_buffer, u8 value, usize byte_count)
{
    WriteonlyBytes destination = reinterpret_cast<WriteonlyBytes>(destination_buffer);
    for (usize offset = 0; offset < byte_count; ++offset) {
        destination[offset] = value;
    }
}

void zero_memory(void* destination_buffer, usize byte_count)
{
    WriteonlyBytes destination = reinterpret_cast<WriteonlyBytes>(destination_buffer);
    for (usize offset = 0; offset < byte_count; ++offset) {
        destination[offset] = 0;
    }
}

} // namespace AT

void* operator new(size_t byte_count, void* memory_block)
{
    (void)byte_count;
    return memory_block;
}