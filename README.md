
# Zit-Zit-Tchat

ZZT is an Olive Tchat Server/Client solution for all. 
But mainly our networks course project !

##Specifications 

###Server

* TCP
* Support multiclients
* Software <port> "String"

###Protocole

* On connexion !hello "String"
* !<command> 
	** list
	** login [a-Z0-1]
	** version
	** message <* | @login>
	** quit

###Architecture

* Port 

	** State **Bind** **Listen**

* Structure Client

	** Socket (int)
	** Login (char)
	** Next (Client)

![ZZT Tchat Architecture ](images/architecture_CS.png?raw=true "Client-Server Architecture")
![Client Architecture ](images/mindmap.png?raw=true "Client-Port Architecture ")
## Getting Started

* Client 

```
ZZTc <port> "String name of the Channel"
```

* Server

```
ZZTs <port> "String name of the Channel"
```

### Prerequisites

* Linux computer

* BSD socket API

### Installing

In order to install Zit-Zit-Tchat you have to clone the repositorie

```
git clone https://github.com/yadev83/Zit-Zit-Tchat.git
```

Go in the folder and make 

```
make
```

Ready to use the ZIT ZITOUN CHAT


## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use Gitkraken and Sublime-Merge

## Authors

* **Yanis Attia** - https://github.com/yadev83
* **Martin Cortopassi** - https://github.com/MartinCorto
* **Valentin Bru**  - https://github.com/Dunateo
* **Jean-Christophe Sanchez**  - https://github.com/JCLEBG

## License

This project is licensed under the Apache License 2.0 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Huile d'olive
* JC for the logo
* Corto ginger
