# tuples are basically lists, but have one key difference: they are immutable
# they are created using (...), except for [...]
tuple1 = (1, 2, 3, 4, 5)
print(tuple1[4])

# indexing
tuple2 = ("a", "a", "b")
print(tuple2.count("a"))
print(tuple2.index("a"))

# these return an error
# print(tuple2.index("c"))
# tuple2[1] = "anythingElse"
