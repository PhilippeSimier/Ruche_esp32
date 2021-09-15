# Le protocole AX25

## 1- Présentation
Le **AX25** est un protocole de niveau **2** couche de liaison du Modèle OSI. Son but est de définir un mécanisme pour **délimiter des trames** de différents types, en ajoutant un contrôle d'erreur.

## 2 - Trame

|Fanion | Adresses | Type de trame | Protocole | Données | Fcs | Fanion |
|--|--|--|--|--|--|--|
|0x7E  |  |0x03|0xFE | data APRS | CRC16 | 0x7E |

### Le fanion
Le fanion est un délimiteur de trame pour la synchronisation. Sa valeur est **01111110** en hexa **0x7E** 

### Les adresses

Le champ d'adresse identifie à la fois l’adresse **source** de la trame et son adresse de  **destination**. l'adresse de destination étant indiquée en premier. De plus, le champ d'adresse contient des informations pour le fonctionnement des répéteurs de couche 2.

L’émetteur peut utiliser des stations intermédiaires appelées digipeaters pour spécifier un itinéraire à emprunter par les paquets. En faisant passer des paquets le long d'une série de répéteurs numériques, les stations qui sont normalement hors de portée peuvent se connecter les unes aux autres.

Le chaînage des répéteurs devrait appartenir à une couche de protocole supérieure, la couche 3 réseau. Par conséquent, ce chaînage devrait être supprimée de la couche 2, toutefois pour maintenir la compatibilité descendante, deux adresses de répéteurs sont maintenus.

Chaque adresse se compose d'un indicatif d'appel et d'un identificateur de station secondaire (SSID).   Exemple **F4ABC-1**

L'indicatif d'appel est composé uniquement de caractères alphanumériques majuscules et ASCII. Le SSID est un entier de quatre bits qui identifie de manière unique plusieurs stations utilisant le même indicatif d'appel amateur (entier compris entre 0 et 15).

La longueur du champs d'adresses est variable.
Le champ d'adresse est étendu au-delà d'un octet en attribuant au bit le moins significatif de chaque octet à un « bit d'extension ». Le bit d'extension de chaque octet est mis à "0" pour indiquer que l'octet suivant contient plus d'informations d'adresse, ou à "1", pour indiquer qu'il s'agit du dernier octet du champ d'adresse. Pour faire  la place à ce bit d'extension, **les informations d'indicatif d'appel radio amateur sont décalées d'un bit vers la gauche**.

### Type de trame
Ce champ permet de distinguer 3 types de trames :

 - 01 trame d'information
 - 02 trame de supervision
 - 03 trame non numérotée
le protocole APRS utilise uniquement les trame non numérotée code 0x03.

### Protocole
Ce champ identifie le type de protocole de niveau 3 (couche réseau) éventuellement utilisé.
La valeur 0xF0 identifie l'absence de protocole de niveau 3.
### Données
Ce champ optionnel de longueur variable contient les données APRS à envoyer. Le nombre de bits à expédier  est un multiple de 8.

### FCS
_Frame Check Sequence_ : le FCS est un code ajouté après les données pour détecter d'éventuelles erreurs de transmission. Il est codé sur 16 bits. 
Cette séquence correspond au CRC  "Cyclic redundancy check"  calculé sur les champs _adresse + commande + données_.

## 3 Transparence (bit stuffing)
Pour que le fanion serve de délimiteur, il est indispensable que la valeur de celui-ci ne se trouve pas dans les données transportées entre le début et la fin. Pour cela, les données seront modifiées pour éliminer les séquences de bits **01111110** (7Eh).  La méthode utilisé est la méthode appelée bourrage de bit, _Bit stuffing_ en anglais.
il s'agit d'éviter de rencontrer six bits consécutifs de valeur _1_. Lors de l'écriture de la trame, si les données contiennent 5 bits successifs à la valeur 1, un 0 est automatiquement ajouté après. Les bits supplémentaire après 5 bits à un successif sont ignorés par le récepteur.
Ainsi il n'y a pas, pendant la transmission, de confusion possible entre données et fanions de début/fin.
