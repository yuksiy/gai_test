# gai_test

## 概要

IPv6 宛先アドレス選択のテストツール

## 使用方法

### gai_test

    指定した宛先ホスト名に関して、選択されるIPアドレスの優先順序を確認します。
    gai_test 宛先ホスト名

    以下のように表示された場合、IPv6 アドレスが優先されています。
    IPv6 アドレス
    IPv4 アドレス

    以下のように表示された場合、IPv4 アドレスが優先されています。
    IPv4 アドレス
    IPv6 アドレス

## 動作環境

OS:

* Linux (Debian)
* Cygwin (MinGW-w64)

依存パッケージ または 依存コマンド:

* make
* binutils (stripコマンド等)
* gcc (Debian のみ)
* mingw64-x86_64-gcc-core (MinGW-w64 のみ)

## インストール

ソースからインストールする場合:

    (Debian の場合)
    $ cd build
    $ make
    $ sudo make install

    (MinGW-w64 の場合)
    $ cd build
    $ make ENVTYPE=mingw-w64
    $ make ENVTYPE=mingw-w64 install

[fil_pkg.pl](https://github.com/yuksiy/fil_tools_pl/blob/master/README.md#fil_pkgpl)
を使用してインストールする場合:

    (Debian の場合)
    $ cd build
    $ make
    $ fakeroot make ENVTYPE=debian pkg
    $ sudo fil_pkg.pl install -C 1 gai_test-*.debian.tar.gz

    (MinGW-w64 の場合)
    $ cd build
    $ make ENVTYPE=mingw-w64
    $ make ENVTYPE=mingw-w64 pkg
    $ fil_pkg.pl install -C 1 gai_test-*.mingw-w64.tar.gz

## インストール後の設定

環境変数「PATH」にインストール先ディレクトリを追加してください。

## 最新版の入手先

<https://github.com/yuksiy/gai_test>

## License

MIT License. See [LICENSE](https://github.com/yuksiy/gai_test/blob/master/LICENSE) file.

## Copyright

Copyright (c) 2011-2017 Yukio Shiiya
