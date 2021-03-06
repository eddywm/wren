// Generated automatically from src/optional/wren_opt_random.wren. Do not edit.
static const char* randomModuleSource =
"foreign class Random {\n"
"  construct new() {\n"
"    seed_()\n"
"  }\n"
"\n"
"  construct new(seed) {\n"
"    if (seed is Num) {\n"
"      seed_(seed)\n"
"    } else if (seed is Sequence) {\n"
"      if (seed.isEmpty) Fiber.abort(\"Sequence cannot be empty.\")\n"
"\n"
"      // TODO: Empty sequence.\n"
"      var seeds = []\n"
"      for (element in seed) {\n"
"        if (!(element is Num)) Fiber.abort(\"Sequence elements must all be numbers.\")\n"
"\n"
"        seeds.add(element)\n"
"        if (seeds.count == 16) break\n"
"      }\n"
"\n"
"      // Cycle the values to fill in any missing slots.\n"
"      var i = 0\n"
"      while (seeds.count < 16) {\n"
"        seeds.add(seeds[i])\n"
"        i = i + 1\n"
"      }\n"
"\n"
"      seed_(\n"
"          seeds[0], seeds[1], seeds[2], seeds[3],\n"
"          seeds[4], seeds[5], seeds[6], seeds[7],\n"
"          seeds[8], seeds[9], seeds[10], seeds[11],\n"
"          seeds[12], seeds[13], seeds[14], seeds[15])\n"
"    } else {\n"
"      Fiber.abort(\"Seed must be a number or a sequence of numbers.\")\n"
"    }\n"
"  }\n"
"\n"
"  foreign seed_()\n"
"  foreign seed_(seed)\n"
"  foreign seed_(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16)\n"
"\n"
"  foreign float()\n"
"  float(end) { float() * end }\n"
"  float(start, end) { float() * (end - start) + start }\n"
"\n"
"  foreign int()\n"
"  int(end) { (float() * end).floor }\n"
"  int(start, end) { (float() * (end - start)).floor + start }\n"
"\n"
"  sample(list) { sample(list, 1)[0] }\n"
"  sample(list, count) {\n"
"    if (count > list.count) Fiber.abort(\"Not enough elements to sample.\")\n"
"\n"
"    // There at (at least) two simple algorithms for choosing a number of\n"
"    // samples from a list without replacement -- where we don't pick the same\n"
"    // element more than once.\n"
"    //\n"
"    // The first is faster when the number of samples is small relative to the\n"
"    // size of the collection. In many cases, it avoids scanning the entire\n"
"    // list. In the common case of just wanting one sample, it's a single\n"
"    // random index lookup.\n"
"    //\n"
"    // However, its performance degrades badly as the sample size increases.\n"
"    // Vitter's algorithm always scans the entire list, but it's also always\n"
"    // O(n).\n"
"    //\n"
"    // The cutoff point between the two follows a quadratic curve on the same\n"
"    // size. Based on some empirical testing, scaling that by 5 seems to fit\n"
"    // pretty closely and chooses the fastest one for the given sample and\n"
"    // collection size.\n"
"    if (count * count * 5 < list.count) {\n"
"      // Pick random elements and retry if you hit a previously chosen one.\n"
"      var picked = {}\n"
"      var result = []\n"
"      for (i in 0...count) {\n"
"        // Find an index that we haven't already selected.\n"
"        var index\n"
"        while (true) {\n"
"          index = int(count)\n"
"          if (!picked.containsKey(index)) break\n"
"        }\n"
"\n"
"        picked[index] = true\n"
"        result.add(list[index])\n"
"      }\n"
"\n"
"      return result\n"
"    } else {\n"
"      // Jeffrey Vitter's Algorithm R.\n"
"\n"
"      // Fill the reservoir with the first elements in the list.\n"
"      var result = list[0...count]\n"
"\n"
"      // We want to ensure the results are always in random order, so shuffle\n"
"      // them. In cases where the sample size is the entire collection, this\n"
"      // devolves to running Fisher-Yates on a copy of the list.\n"
"      shuffle(result)\n"
"\n"
"      // Now walk the rest of the list. For each element, randomly consider\n"
"      // replacing one of the reservoir elements with it. The probability here\n"
"      // works out such that it does this uniformly.\n"
"      for (i in count...list.count) {\n"
"        var slot = int(0, i + 1)\n"
"        if (slot < count) result[slot] = list[i]\n"
"      }\n"
"\n"
"      return result\n"
"    }\n"
"  }\n"
"\n"
"  shuffle(list) {\n"
"    if (list.isEmpty) return\n"
"\n"
"    // Fisher-Yates shuffle.\n"
"    for (i in 0...list.count - 1) {\n"
"      var from = int(i, list.count)\n"
"      var temp = list[from]\n"
"      list[from] = list[i]\n"
"      list[i] = temp\n"
"    }\n"
"  }\n"
"}\n";
