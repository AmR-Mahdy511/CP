## Quick Notes

- `next[][]`: at each node, where to go when we put any character.
- `link[]`: at each node, the longest proper suffix I can match.
- `out_link[]`: at each node, the longest proper suffix I can match that has a pattern.
- `out[][]`: at each node, a vector of pattern indices.

---

# Aho-Corasick

Aho-Corasick is a string matching algorithm used to find **multiple
patterns** inside a text efficiently.

It is basically:

> **Trie + Failure Links + Output**

## Main Idea

1.  Insert all patterns into a **Trie**.
2.  Build `link[]` (failure links) using BFS.
3.  Scan the text once using the Trie + failure links.
4.  When a pattern is reached, it is found.

### Example

Patterns:

``` text
he
she
hers
```

Text:

``` text
ushers
```

The algorithm can find all patterns in one pass.

------------------------------------------------------------------------

## Important Arrays

### `next[u][c]`

The transition from node `u` using character `c`.

After building the automaton, it tells us where to go directly when we
read a character.

### `link[u]`

The node to **fall back to** when the current node cannot continue with
the next character.

This is similar to the **KMP failure / prefix function** idea: instead
of starting over from the beginning, we fall back to the longest useful
suffix that can still be matched.

It represents the node corresponding to the **longest proper suffix** of
the current string that is also a prefix in the Trie.

``` text
she → he
```

because `he` is the longest proper suffix of `she` that is also a Trie
prefix.

### `out_link[u]`

Points to the node representing the **longest proper suffix** of the
current string that also corresponds to a pattern.

Useful for finding patterns that are contained inside another matched
pattern.

Example:

``` text
she → he
```

If both `she` and `he` are patterns, `out_link[she] = he`.

### `out[u]`

Stores the indices of patterns that **end at node `u`**.

``` cpp
out[u] = {pattern indices};
```

------------------------------------------------------------------------

## Failure Link vs Output Link

-   `link[u]`: longest proper suffix that is also a **Trie prefix**.
-   `out_link[u]`: longest proper suffix that is also a **pattern**.

------------------------------------------------------------------------

## Complexity

For `N` = total length of all patterns and `M` = text length:

-   Build Trie: `O(N)`
-   Build Failure Links: `O(N * alphabet)` in this implementation
-   Search: `O(M)`
-   Memory: `O(N * alphabet)`

For lowercase English letters, `alphabet = 26`.

------------------------------------------------------------------------

## Quick Reminder

``` text
Aho-Corasick
    |
    +-- Trie
    |
    +-- link[]      -> where to fail (similar to KMP fallback)
    |
    +-- out_link[]  -> next suffix that has a pattern
    |
    +-- out[]       -> patterns ending here
    |
    +-- next[][]    -> transitions
```

### One sentence to remember

> **Aho-Corasick = Trie + failure links, allowing us to search for many
> patterns in a text without restarting from the beginning whenever a
> match fails.**
