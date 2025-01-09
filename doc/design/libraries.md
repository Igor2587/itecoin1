# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libItecoin_cli*         | RPC client functionality used by *Itecoin-cli* executable |
| *libItecoin_common*      | Home for common functionality shared by different executables and libraries. Similar to *libItecoin_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libItecoin_consensus*   | Stable, backwards-compatible consensus functionality used by *libItecoin_node* and *libItecoin_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libItecoinconsensus*    | Shared library build of static *libItecoin_consensus* library |
| *libItecoin_kernel*      | Consensus engine and support library used for validation by *libItecoin_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libItecoinqt*           | GUI functionality used by *Itecoin-qt* and *Itecoin-gui* executables |
| *libItecoin_ipc*         | IPC functionality used by *Itecoin-node*, *Itecoin-wallet*, *Itecoin-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libItecoin_node*        | P2P and RPC server functionality used by *Itecoind* and *Itecoin-qt* executables. |
| *libItecoin_util*        | Home for common functionality shared by different executables and libraries. Similar to *libItecoin_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libItecoin_wallet*      | Wallet functionality used by *Itecoind* and *Itecoin-wallet* executables. |
| *libItecoin_wallet_tool* | Lower-level wallet functionality used by *Itecoin-wallet* executable. |
| *libItecoin_zmq*         | [ZeroMQ](../zmq.md) functionality used by *Itecoind* and *Itecoin-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libItecoin_consensus* and *libItecoin_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libItecoin_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libItecoin_node* code lives in `src/node/` in the `node::` namespace
  - *libItecoin_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libItecoin_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libItecoin_util* code lives in `src/util/` in the `util::` namespace
  - *libItecoin_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

Itecoin-cli[Itecoin-cli]-->libItecoin_cli;

Itecoind[Itecoind]-->libItecoin_node;
Itecoind[Itecoind]-->libItecoin_wallet;

Itecoin-qt[Itecoin-qt]-->libItecoin_node;
Itecoin-qt[Itecoin-qt]-->libItecoinqt;
Itecoin-qt[Itecoin-qt]-->libItecoin_wallet;

Itecoin-wallet[Itecoin-wallet]-->libItecoin_wallet;
Itecoin-wallet[Itecoin-wallet]-->libItecoin_wallet_tool;

libItecoin_cli-->libItecoin_util;
libItecoin_cli-->libItecoin_common;

libItecoin_common-->libItecoin_consensus;
libItecoin_common-->libItecoin_util;

libItecoin_kernel-->libItecoin_consensus;
libItecoin_kernel-->libItecoin_util;

libItecoin_node-->libItecoin_consensus;
libItecoin_node-->libItecoin_kernel;
libItecoin_node-->libItecoin_common;
libItecoin_node-->libItecoin_util;

libItecoinqt-->libItecoin_common;
libItecoinqt-->libItecoin_util;

libItecoin_wallet-->libItecoin_common;
libItecoin_wallet-->libItecoin_util;

libItecoin_wallet_tool-->libItecoin_wallet;
libItecoin_wallet_tool-->libItecoin_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class Itecoin-qt,Itecoind,Itecoin-cli,Itecoin-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libItecoin_wallet* and *libItecoin_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libItecoin_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libItecoin_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libItecoin_common* should serve a similar function as *libItecoin_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libItecoin_util* and *libItecoin_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for Itecoin-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libItecoin_kernel* is not supposed to depend on *libItecoin_common*, only *libItecoin_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libItecoin_kernel* should only depend on *libItecoin_util* and *libItecoin_consensus*.

- The only thing that should depend on *libItecoin_kernel* internally should be *libItecoin_node*. GUI and wallet libraries *libItecoinqt* and *libItecoin_wallet* in particular should not depend on *libItecoin_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libItecoin_consensus*, *libItecoin_common*, and *libItecoin_util*, instead of *libItecoin_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libItecoinqt*, *libItecoin_node*, *libItecoin_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libItecoin_node* to *libItecoin_kernel* as part of [The libItecoinkernel Project #24303](https://github.com/Itecoin/Itecoin/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/Itecoin/Itecoin/issues/15732)
