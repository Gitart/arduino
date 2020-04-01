
For install ubuntu

https://forum.fritzing.org/t/fixing-fritzing-on-ubuntu-18-04/6504


## I started out by removing all Fritzing related files:

```
sudo apt purge fritzing*
sudo apt autoremove
```

## Then I removed the config folder:

```
rm -rf ~/.config/Fritzing/
```

## Next I reïnstalled Fritzing:

```
sudo apt update
sudo apt install fritzing
```


## It is clear that the parts are simply not available. To fix this, we can download them seperately from github:

```
cd /usr/share/fritzing/
sudo git clone https://github.com/fritzing/fritzing-parts.git
sudo mv fritzing-parts/ parts
```



