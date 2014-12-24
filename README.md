Umbrella is a language which tries to focus on the process of the program rather than the computer's requirements.
While such an approach could be detrimental to efficiency, Umbrella aims to optimize heavily to obviate this.

By "process oriented", I mean a higher level language that neither worrys about the machine nor losing too much efficiency.
Umbrella has first class functions and types.  Instead of having classes and objects, it has traits and types.
A trait is some sort of attribute like being addable, and all types that have a trait must define certain functions.
This system is inspired by Haskell, as is much of the Umbrella's syntax.

Some examples:

`type name = some stuff`

`type Tree = Node a b | Null`

Here, a Tree could be set to Null or Node a b.
For traits, you would have something like:

    trait Addable _ =
        (+)

A type with the Addable trait would need to define `(+)`

To make our Tree type have the trait, we can write:

    `trait Addable Tree =
        (Node a b + Node c d) = Node (a+c) (b+d)
        (_ + Null) = Null
        (Null + Null) = Null

This uses patten matching to figure out whether the Trees are Nodes or Nulls.
Pattern matching is great.

The really great part about traits is that functions can take a trait instead of a type, meaning functions are automatically generic in a logical way,
instead of tied to a type, like in C, which makes no sense if you think about what a function is doing conceptually.
So a type is a representation of data and a function is an action, an action which should be valid for any representation of data sharing some aspect.
Thus, types and traits.

In Umbrella, `value:type` is used a lot to explicitly cast something to a certain type.

For a more full description of Umbrella's syntax, you can look at features.txt, but it is not very well formatted.
You can also check out the source code in source_tests, but there is none yet.

