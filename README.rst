======
LFSR64
======

A simple 64-bit `linear feedback shift register
<http://en.wikipedia.org/wiki/Linear_feedback_shift_register>`_,
printing pseudo-random bytes to stdout.

A Galois configuration LFSR via [1]_ with Stahnke's 64-bit tap positions
[2]_, I pre-compute the combined feedback terms for a byte's worth of
output and bulk-xor them in for a ~2x speedup over iterating bit-by-bit
(I forget where I first saw that technique).

.. [1] `Maximal Length LFSR Feedback Terms
   <http://users.ece.cmu.edu/~koopman/lfsr/index.html>`_
.. [2] Wayne Stahnke. *Primitive binary polynomials*. Math. Comp. 27
   (1973) 977-980. MR `0327722
   <http://www.ams.org/mathscinet-getitem?mr=327722>`_

*****
Build
*****

I build with clang, like so::

  clang -O3 -Wall -o lfsr64 lfsr64.c

***
Use
***

Usage::

  usage: ./lfsr64 [seed]

The seed is optional, if not present it will default to ``time(3)``.
Zero is not valid as the seed value, as that would lock the LFSR in
a permanent all-zeros state.

Check the health of a block device::

  # lfsr64 $$ | dd iflag=fullblock bs=256k of=/dev/foo
  # cmp <(lfsr64 $$) /dev/foo

The lazyweb suggests that ``oflag=dsync`` can help with "task blkid:NNNN
blocked for more than 120 seconds" errors on slow USB sticks. If the
sink is faster than this source, ``iflag=fullblock`` will stop partial
blocks from being passed through to the sink.
