// Prevent multiple inclusion of this header
#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

// Runs the pathfinding algorithm on the provided level string.  The
// callback is periodically invoked with the progress percentage.  The
// operation can be cancelled via the `stop` flag.  The result is a
// serialized replay in the GDR format.
std::vector<uint8_t> pathfind(
    std::string const& lvlString,
    std::atomic_bool& stop,
    std::function<void(double)> callback);
