import sys, eol

def main():
  print r'Convert EOL between Windows(\r\n) and Unix(\n)'
  args = sys.argv[1:]
  if not args:
    print 'usage: [--r] --w2u/--u2w';
    sys.exit(1)
  Rec = False
  if args[0] == '--r':
    Rec = True
    del args[0]
  if len(args) == 0:
    print 'error command'
    sys.exit(1)
  elif args[0] == '--w2u': EOL = '\n'
  elif args[0] == '--u2w': EOL = '\r\n'
  else:
    print 'error command'
    sys.exit(1)
  eol.convert_path_patterns_eol(['.'], EOL, recursive=Rec, excludes=['.git', 'convertEOL.py'])

# This is the standard boilerplate that calls the main() function.
if __name__ == '__main__':
  main()
