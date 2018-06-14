# vagrant sshしたらまっさらなVMがそこにあった
環境 
Ubuntu 16.04 LTS
vagrant 2.1.1
VirtualBox Graphical User Interface Version 5.1.34_Ubuntu r121010

# homeディレクトリ以下にあったディレクトリが消えている
```
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Importing base box 'bento/centos-7.2'...
==> default: Matching MAC address for NAT networking...
==> default: Checking if box 'bento/centos-7.2' is up to date...
==> default: Setting the name of the VM: rails_tutorial_default_1528677272770_17615
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
    default: Adapter 2: hostonly
==> default: Forwarding ports...
    default: 22 (guest) => 2222 (host) (adapter 1)
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: vagrant
    default: SSH auth method: private key
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: 
    default: Vagrant insecure key detected. Vagrant will automatically replace
    default: this with a newly generated keypair for better security.
    default: 
    default: Inserting generated public key within guest...
    default: Removing insecure key from the guest if it's present...
    default: Key inserted! Disconnecting and reconnecting using new SSH key...
==> default: Machine booted and ready!
==> default: Checking for guest additions in VM...
==> default: Configuring and enabling network interfaces...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: vagrant
    default: SSH auth method: private key
==> default: Mounting shared folders...
    default: /vagrant => /home/hoyamag/Codes/rails_tutorial
$ vagrant ssh
[vagrant@localhost ~]$ ls
[vagrant@localhost ~]$ ls
[vagrant@localhost ~]$ ls -a
.  ..  .bash_logout  .bash_profile  .bashrc  .ssh  .vbox_version
[vagrant@localhost ~]$ logout
```

# 入れていたソフトも抜けている
[vagrant@localhost ~]$ rails
-bash: rails: command not found

# vagrant vm 消えたでぐぐる
どうやら既知の現象らしいです
[vagrant upすると、以前インストールしたRubyやRailsなどの中身がすべて消えてしまう。](http://twosquirrel.mints.ne.jp/?p=5100)
今まであったVMは消えたわけではなく、連携が切れただけのようです。
その状態で'vagrant up'したため新規のVMが作成されたという。

ただ、ここで直し方として紹介されている
[Vagrantの仮想マシンとの紐付けの直し方 - ウチのメモ](http://elm-arata.hatenablog.com/entry/2013/09/25/175547)
がvagrant 1.2.7向けの話だからか、「.vagrantファイルを修正して直す」の部分が自分の環境と合致しませんした(.vagrantはディレクトリなので)。
ということで'vagrant vm missing'でぐぐってそれっぽいページを見つけました(
[Re-associate vagrant with vm · Issue #1755 · hashicorp/vagrant · GitHub](https://github.com/hashicorｔ/vagrant/issues/1755))。
手順がわかったので直します。

# 結論
直りました。
実際の手順を知りたい方は「やった手順(ログ目的のため失敗手順含む)」を参照してください。
結論としては[Vagrant lost all of my VMs · Issue #5144 · hashicorp/vagrant · GitHub](https://github.com/hashicorp/vagrant/issues/5144)
を見るのが一番でした。
再発防止策としては、下記が有効そうな気がします(試してません)。

* 'vagrant up'する前に'VBoxManage list vms'してVMが紐付いているか確認する
* boxファイルを作って復旧を容易にしておく(参考:[自分仕様のboxファイルを作成する](https://qiita.com/darwin/items/c473b7c54e61b2acb7e5))
* .vagrantフォルダをバックアップしておく(？)

# やった手順(ログ目的のため失敗手順含む)
## vagrantとVMの紐付けの回復
VirtualBoxのVMはディレクトリ'~/VirtualBox\ VMs/'にあるそうなので、そこにあるVMを確認します(コマンド'VBoxManage list vms'だと、1つしかVMが出てこなかったので)。
```
hoyamag@hoyThinkpad13:~/VirtualBox VMs$ ll
total 20
drwx------  5 hoyamag hoyamag 4096  6月 11 09:34 ./
drwxr-xr-x 45 hoyamag hoyamag 4096  6月 11 22:51 ../
drwx------  3 hoyamag hoyamag 4096  5月 17 07:23 rails_tutorial_default_1526509377188/
drwx------  3 hoyamag hoyamag 4096  6月  7 09:23 rails_tutorial_default_1526511117537/
drwx------  3 hoyamag hoyamag 4096  6月 11 09:34 rails_tutorial_default_1528677272770/
```
行方不明のVMの名前がわからず、最終更新日付が見たかったのでllを使いました。
ということで行方不明のVMの居所がわかりました。
次はvagrantとこのVMとの紐付けを回復します。

* ファイル'$(your_vagrant_directory)/.vagrant/machines/default/virtualbox/id'に記載されているIDのVMが、そのディレクトリで'vagrant up'したときに起動される
* VMのIDはXMLファイル'~/VirtualBox\ VMs/\$(your_missing_VM_name)/$(your_missing_VM_name).vbox'のMachineタグの属性uuidに書いてある。

(UUIDってなんだ？って思ったんですけど、Universally Unique Identifierで世界中で重複しないIDらしいです)
ということなので、idファイルに書いてあるUUIDを、起動したいVMのUUIDで置き換えました。

'vagrant up'
'vagrant ssh'
したら、また新たなVMが生成されたようで、目的のVMにアクセスすることは出来ませんでした。
多分目的のVMが起動していないので、'vagrant up'実行時に”存在しない”判定になり、新規のVMが生成されているような気がします。
試しにVirtualBoxをGUIで立ち上げると、リストに目的のVMがリストされていません。

## なぜかVMとVirtualBoxとの紐付けが切れているようなので、VMをVirtualBoxにインポートする
'VirtualBox missing VM'でぐぐります。
[virtualbox.org • View topic - missing virtual machines, but the XML files exist....](https://forums.virtualbox.org/viewtopic.php?f=2&t=37708)
を見ると、”'VBoxManage registervm'で直せたよ。詳細はここを見てね”みたいなことが書いてあるのでそこを見ます。
[Chapter�8.�VBoxManage](http://www.virtualbox.org/manual/ch08.html#vboxmanage-registervm)/.
「XMLファイルに書かれたVM定義をVirtualBoxにインポートできます」みたいなことが書いてます。
syntaxが書いてないので
'VBoxManage --version > ~/a.txt'
'vim ~/a.txt'
してregistervmオプションの使い方を見ます。ファイルネームを指定すれば良さそうです。

'VBoxManage registervm <fullpath.vbox>'
実行したらエラーメッセージもなく終わりました(fullpathは長かったので除いています)。
'VirtualBox'
してVirtualBoxのGUIを見ると目的のVMがリストされているので大丈夫そうです。

いつも'vagrant up'してたディレクトリで'vagrant up'します。
```
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Checking if box 'bento/centos-7.2' is up to date...
==> default: Clearing any previously set forwarded ports...
==> default: Fixed port collision for 22 => 2222. Now on port 2201.
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
    default: Adapter 2: hostonly
==> default: Forwarding ports...
    default: 22 (guest) => 2201 (host) (adapter 1)
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2201
    default: SSH username: vagrant
    default: SSH auth method: private key
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Authentication failure. Retrying...
    default: Warning: Authentication failure. Retrying...
    default: Warning: Authentication failure. Retrying...
    default: Warning: Authentication failure. Retrying...
^C==> default: Waiting for cleanup before exiting...
Vagrant exited after cleanup due to external interrupt.
$ VirtualBox 
```
Authentication(認証？)が通りません。

## ssh接続の回復
### しばらく失敗手順
なぜauthでエラーになったのか考えます。vagrantとVMの紐付け情報は、さっきの経緯から.vagrantフォルダ以下に保存されてそうです。.vagrantフォルダ以下を一覧します。
```
$ tree .vagrant
.vagrant
└── machines
    └── default
        └── virtualbox
            ├── action_set_name
            ├── creator_uid
            ├── id
            ├── index_uuid
            ├── private_key
            ├── synced_folders
            └── vagrant_cwd

3 directories, 7 files

```
Authenticationのエラーなので、private_keyを適切に置き換えれば動きそうな気がしますが、どう直すかわからないので'vagrant Authentication failure'でぐぐります。

[Vagrant ssh authentication failure - Stack Overflow](https://stackoverflow.com/questions/22922891/vagrant-ssh-authentication-failure)
VagrantFileに~/.ssh/id_rsaを使うように設定した。
いわく、「

* ファイルVagrantfileに「ssh private keyを格納したファイルを指定する記述を追加」し
* 対応するpublic keyをVMに追加する

とAuthenticationが通るようになるだろう」とのこと。指示に従います。

'vim Vagrantfile'
して、もともと
```
...
Vagrant.configure("2") do |config|
...
```

だったのを
```
...
Vagrant.configure("2") do |config|
  config.ssh.private_key_path = "~/.ssh/id_rsa"
  config.ssh.forward_agent = true
...
```
にしました。
そして、'ssh-copy-id -p 2222 root@127.0.0.1'しました。
```
$ ssh-copy-id -p 2222 root@127.0.0.1
The authenticity of host '[127.0.0.1]:2222 ([127.0.0.1]:2222)' can't be established.
ECDSA key fingerprint is SHA256:DrnHAeFdOksJ55bMSmPERVhLTW2ft2gWxXloYREdYbY.
Are you sure you want to continue connecting (yes/no)? yes
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
root@127.0.0.1's password: 
Connection to 127.0.0.1 closed by remote host.
```
パスワードがわかりません。。。  
'Virtual Box default password'  
'CentOS default password'
でぐぐりますがいい感じのが出てきません。。。

'vagrant vm missing'
でググり直して2番めのページを見ます
[Vagrant lost all of my VMs · Issue #5144 · hashicorp/vagrant · GitHub](https://github.com/hashicorp/vagrant/issues/5144)
のJan 9, 2015投稿のStep9に「じゃあ起動しなおしたVMにid/password vagrant/vagrantでログインしてみようか」みたいなことが書いてあります(同時にこの投稿詳しすぎて最初からここ見ればよかった疑惑も立ちます)。

id/passwordがわかったのでさっきの手順を再開します
```
$ ssh-copy-id -p 2222 root@127.0.0.1
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
root@127.0.0.1's password: 

Number of key(s) added: 1

Now try logging into the machine, with:   "ssh -p '2222' 'root@127.0.0.1'"
and check to make sure that only the key(s) you wanted were added.
```
idはvagrantであることを思い出したので、再実行します。
```
$ ssh-copy-id -p 2222 vagrant@127.0.0.1
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
vagrant@127.0.0.1's password: 

Number of key(s) added: 1

Now try logging into the machine, with:   "ssh -p '2222' 'vagrant@127.0.0.1'"
and check to make sure that only the key(s) you wanted were added.
```
vagrant reload(再起動？)します
```
$ vagrant reload
==> default: Attempting graceful shutdown of VM...
    default: Guest communication could not be established! This is usually because
    default: SSH is not running, the authentication information was changed,
    default: or some other networking issue. Vagrant will force halt, if
    default: capable.
==> default: Forcing shutdown of VM...
==> default: Checking if box 'bento/centos-7.2' is up to date...
==> default: Clearing any previously set forwarded ports...
==> default: Fixed port collision for 22 => 2222. Now on port 2201.
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
    default: Adapter 2: hostonly
==> default: Forwarding ports...
    default: 22 (guest) => 2201 (host) (adapter 1)
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2201
    default: SSH username: vagrant
    default: SSH auth method: private key
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Authentication failure. Retrying...
^C==> default: Waiting for cleanup before exiting...
    default: Warning: Connection refused. Retrying...
Vagrant exited after cleanup due to external interrupt.
```
だめでした。
'vagrant change ssh key'でググってみたんですが、出てきたページが
[config.ssh - Vagrantfile - Vagrant by HashiCorp](https://www.vagrantup.com/docs/vagrantfile/ssh_settings.html)で、もはや読む元気がありませんでした。

### 実際に有効だったssh接続回復手段
vagrant issue #5144の2番目のコメントに従います。
[Vagrant lost all of my VMs · Issue #5144 · hashicorp/vagrant · GitHub](https://github.com/hashicorp/vagrant/issues/5144)

```
$ cp ~/.vagrant.d/insecure_private_key ./.vagrant/machines/default/virtualbox/private_key 
$ vagrant ssh-config
Host default
  HostName 127.0.0.1
  User vagrant
  Port 2201
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /home/hoyamag/Codes/rails_tutorial/.vagrant/machines/default/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL
$ VirtualBox
```
vagrantで管理してたVMに
id/padd=vagrant/vagrantでログインして
```
wget https://raw.githubusercontent.com/mitchellh/vagrant/master/keys/vagrant.pub
cat vagrant.pub >> .ssh/authorized_keys
```
元いたターミナルに戻って
```
$ vagrant halt
==> default: Attempting graceful shutdown of VM...
    default: 
    default: Vagrant insecure key detected. Vagrant will automatically replace
    default: this with a newly generated keypair for better security.
    default: 
    default: Inserting generated public key within guest...
    default: Removing insecure key from the guest if it's present...
    default: Key inserted! Disconnecting and reconnecting using new SSH key...
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Checking if box 'bento/centos-7.2' is up to date...
==> default: Clearing any previously set forwarded ports...
==> default: Fixed port collision for 22 => 2222. Now on port 2201.
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
    default: Adapter 2: hostonly
==> default: Forwarding ports...
    default: 22 (guest) => 2201 (host) (adapter 1)
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2201
    default: SSH username: vagrant
    default: SSH auth method: private key
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...
==> default: Machine booted and ready!
==> default: Checking for guest additions in VM...
==> default: Configuring and enabling network interfaces...
    default: SSH address: 127.0.0.1:2201
    default: SSH username: vagrant
    default: SSH auth method: private key
==> default: Mounting shared folders...
    default: /vagrant => /home/hoyamag/Codes/rails_tutorial
==> default: Machine already provisioned. Run `vagrant provision` or use the `--provision`
==> default: flag to force provisioning. Provisioners marked to run always will still run.
$ vagrant ssh
Last login: Tue Jun 12 14:51:48 2018
ls[vagrant@localhost ~]$ ls
environment  vagrant.pub

```
終わりました。
ssh接続の復旧に手間取りましたが、.vagrant/.../idファイルのIDを直して、行方不明だったVMを起動したあたりから、「'varant ssh'を実行してpassword=vagrantで認証してログインする」はできてたと思います(ssh認証に失敗しながらもできてたので)。

