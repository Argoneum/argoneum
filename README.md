Argoneum Core staging tree 1.3.3.1
==================================

Fixed deterministic masternode collateral value.


Argoneum Core staging tree 1.3.3.0
==================================

Updated to Dash core v0.13.3.0.

WARNING: this release uses new masternode options (DIP0003). Do not upgrade unless
prepared to manually update your masternodes. If you use a hosting platform, make
sure that they support DIP0003 masternodes, particularly, masternodeblsprivkey
configuration option.

More info on masternode updates:
 - https://docs.dash.org/en/stable/masternodes/setup.html
 - https://docs.dash.org/en/stable/masternodes/understanding.html#dip3-changes
 - https://docs.dash.org/en/0.13.0/masternodes/dip3-upgrade.html



Argoneum Core staging tree 1.2.3.4
==================================

https://www.argoneum.net

We are going to follow the Dash development and update to the latest codebase
from Dash. Unfortunately, due to the nature of blockchain and features implemented
by Dash team it is not possible to jump directly to the latest version. So a
series of updates is planned as follows:

 - v1.2.3.4 (based on Dash 0.12.3.4, latest in 0.12 series)
 - v1.3.3.0 (based on Dash 0.13.3.0, latest in 0.13 series)
 - v1.4.0.2 (based on Dash 0.14.0.2 or latest)

This is an intermediate beta release of Argoneum software along this way.
This release may (and definitely has) some inaccurate translations, web links
and other minor issues. It also may have invalid copyright strings due to
automated renames. All this will be fixed in the final release.

The original copyrights are held by Bitcoin developers and Dash developers.


What's new in this version
--------------------------

1. New reward table starting from block 555840:

| year | block number | block reward | PoW reward | MN reward | Superblock (governance) reserved |
|------|--------------|--------------|------------|-----------|----------------------------------|
| 2019 |     555840   |       15     |      6     |    7.5    |               1.5                |
| 2020 |    1051201   |        5     |      2     |    2.5    |               0.5                |
| 2025 |    3679201   |        4     |    1.6     |      2    |               0.4                |
| 2030 |    6307201   |        3     |   1.05     |   1.65    |               0.3                |
| 2040 |   11563201   |        2     |    0.8     |      1    |               0.2                |
| 2060 |   22075201   |        1     |   0.44     |   0.46    |               0.1                |
| 2080 |   32587201   |      0.5     |  0.175     |  0.275    |              0.05                |
| 2090 |   37843201   |      0.2     |   0.08     |    0.1    |              0.02                |

2. Enabled governance. Superblock rewards reserved to 10% of total blocks reward per period.

3. Disabled developer fee starting from block 555840. Pools should remove the dev fee starting
   from that block. If they don't do that, they still will fund the Argoneum, but it will not be
   required.



What is Dash?
----------------

Dash is an experimental digital currency that enables anonymous, instant
payments to anyone, anywhere in the world. Dash uses peer-to-peer technology
to operate with no central authority: managing transactions and issuing money
are carried out collectively by the network. Dash Core is the name of the open
source software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Dash Core software, see https://www.dash.org/get-dash/.


License
-------

Dash Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/dashpay/dash/tags) are created to indicate new official,
stable release versions of Dash Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

Changes to translations as well as new translations can be submitted to
[Dash Core's Transifex page](https://www.transifex.com/projects/p/dash/).

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

Translators should also follow the [forum](https://www.dash.org/forum/topic/dash-worldwide-collaboration.88/).
