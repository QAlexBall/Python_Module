from collections.abc import Iterable

def flatten(items, ignore_types=(str, bytes)):
  for x in items:
    if isinstance(x, Iterable) and not isinstance(x, ignore_types):
      yield from flatten(x)
      """
      yield from flattern(x) same like following code.
      for i in flatten(x):
          yield i
      """
    else:
      yield x

items = [1, 2, [3, 4, [5, 6], 7], 8]
for x in flatten(items):
  print(x)