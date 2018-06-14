# neovimにlldbを導入するとき':UpdateRemotePlugins'で詰まった話
環境構築系何もわからないんですが、詰まったら詰まったなりにメモを残しておかないとまた詰まるのでメモを残します。

環境 Ubuntu 16.04 LTS 

手順は大体これに則りました
[neovim + clang + lldbでC++開発環境構築メモ(自動補完、文法チェック、デバッガフロントエンド)](https://qiita.com/grainrigi/items/bd75639085e754795ed4)。
ただ、試行錯誤の過程で

* neovimのプラグインマネージャはvim-plugに
* critiqjo/lldb.nvimはdbgx/lldb.nvimを使うように

なりました。
vim-plugでインストールしたパッケージは~/.local/share/nvim/plugged以下に入るらしい




## 詰まった位置1
lldb.nvimの導入で
```
:UpdateRemotePlugin
```
を実行したところ。
コピーを撮り忘れたが、
```
... 
Failed to load python3 host.
...
```
のようなエラーメッセージが出た。

## 解決策

1. ':CheckHealth'をneovim上で実行すると、neovimのステータスが表示されるらしいので実行する。
2. "python 3 provider (optional)"のところがNGになっており、python3-neovimがインストーされていないことがわかる。
3. 'pip3 install neovim'する。
4. 再度neovim上で':CheckHealth'して、'python 3 provider'がOKになのを確認する
5. ':UpdateRemotePlugins'をneovim上で実行する(今度は通るはず)

## 詰まった位置2
詰まった位置1を解消した後、':PlugInstall'を行った。
その後
```
:UpdateRemotePlugin
```
を行うと
```
...
ImportError: No module named lldb
...
```
のようなエラーメッセージが出た。

## 解決策
エラーメッセージでぐぐると[linux - how to import lldb in a python script - Stack Overflow](https://stackoverflow.com/questions/30869945/how-to-import-lldb-in-a-python-script)に着いたので、Answerの指示の通り、壊れたシンボリックリンクを直す。

