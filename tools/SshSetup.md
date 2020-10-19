# SSH Setup

Windows 10 (for quite a while now) contain `ssh` and `ssh-keygen` command line tools
which enable console logins to remote machines with and without password.

## Remote login with username and password

Simply execute `ssh user@host` to connect.
You will be prompted for the password of the remote host.

## Remote login without password

3 Steps to setup remote login without password:

* Use `ssh-keygen` to create public and private ssh keys,
  which by default will be stored in `~\.ssh\id_rsa.pub` and `~\.ssh\id_rsa`.
  For automatic login use an empty passphrase.

  ```cmd
  ssh-keygen

  Generating public/private rsa key pair.
  Enter file in which to save the key (C:\Users\Mischa/.ssh/id_rsa):
  Enter passphrase (empty for no passphrase):
  Enter same passphrase again:
  Your identification has been saved in C:\Users\Mischa/.ssh/id_rsa.
  Your public key has been saved in C:\Users\Mischa/.ssh/id_rsa.pub.
  ...
  ```

* Use `ssh user@host` to login to the remote host (to update the `known_hosts` file)

* Append the Windows SSH public key to the `.ssh/authorized_keys` file on remote machine,
  e.g. for user `pi` on host `beany`:

  ```cmd
  cd
  cd .ssh
  type id_rsa.pub | ssh pi@beany "cat >> .ssh/authorized_keys"
  ```

Now use of `ssh user@host` should no longer ask for a password.

## VS Code Plugin

The [Remote SSH Plugin](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) makes use on these settings and allows to login from within VS Code and to open remote folders.

For more info see these articles:

* [Visual Studio Code Remote SSH Tips and Tricks](https://code.visualstudio.com/blogs/2019/10/03/remote-ssh-tips-and-tricks)
* [Remote SSH with Visual Studio Code](https://code.visualstudio.com/blogs/2019/07/25/remote-ssh)
* [Visual Studio Code Remote Development over SSH to a Raspberry Pi is butter](https://www.hanselman.com/blog/visual-studio-code-remote-development-over-ssh-to-a-raspberry-pi-is-butter)
