Changelog
=========
2.1.0
-----
- Isolate Logger from LoggerInterface and Level
- Created Printer::Stub()
- Changed std::runtime_error to std::logic_error when Filter/Union receive nullptr

2.0.1
-----
- Adjust header instalation

2.0.0
=====
- Migrated to [xmake](https://xmake.io/) build tools
- Refactor of entirely library
- Require C++20
- Support cascade operations
- Support filter operation
- Support union operation (propagate to more than one `LoggerInterface`)
- Support output to `ostream`, `stdout`, `html`

1.1.1
-----
- Better styles for html
- Added AppVeyor integration

1.1.0
-----
- Created enum Type
- Better code style

1.0.0
-----
- First version