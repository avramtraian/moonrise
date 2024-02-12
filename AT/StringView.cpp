/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#include "AT/StringView.h"
#include "AT/Utf8.h"

namespace AT {

ErrorOr<StringView> StringView::create_from_utf8(const char* characters, usize byte_count)
{
    TRY(UTF8::try_check_validity({ reinterpret_cast<ReadonlyBytes>(characters), byte_count }));
    return unsafe_create_from_utf8(characters, byte_count);
}

ErrorOr<StringView> StringView::create_from_utf8(const char* null_terminated_characters)
{
    TRY_ASSIGN(auto byte_count, UTF8::try_byte_count(reinterpret_cast<ReadonlyBytes>(null_terminated_characters)));
    return unsafe_create_from_utf8(null_terminated_characters, byte_count);
}

usize StringView::find(char ascii_character) const
{
    for (usize offset = 0; offset < m_byte_count; ++offset) {
        if (m_characters[offset] == ascii_character) {
            return offset;
        }
    }

    return invalid_position;
}

usize StringView::find(UnicodeCodepoint codepoint_to_find) const
{
    usize offset = 0;
    while (offset < m_byte_count) {
        usize codepoint_width;
        const auto codepoint = UTF8::bytes_to_codepoint(byte_span().subrange(offset), codepoint_width);
        AT_ASSERT(codepoint != invalid_unicode_codepoint);

        if (codepoint == codepoint_to_find) {
            return offset;
        }
        offset += codepoint_width;
    }

    return invalid_position;
}

} // namespace AT