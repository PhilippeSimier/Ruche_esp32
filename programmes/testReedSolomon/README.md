# RS -FEC 

## 1- **Correction d’erreur sans voie de retour (FEC)**

Comme nous le savons, les signaux radios peuvent parfois se détériorer au cours de la transmission en raison de certains facteurs et cela peut conduire à une erreur de décodage du côté récepteur, qui peut confondre le signal "1" avec le signal "0", ou le signal "0" avec le signal "1". D'inévitables erreurs de décodage  se  produisent   et  il  faut  parer  a  ce  phénomène.  Une  des  réponses possibles réside dans les **codes correcteurs d’erreurs**.
La correction d’erreur sans voie de retour est un procédé dans lequel les résultats des algorithmes sont envoyés comme information supplémentaire avec les données. En répétant les mêmes algorithmes à l’autre extrémité, le récepteur a la possibilité de détecter les erreurs au bit près et de les corriger (erreurs corrigibles) sans devoir demander à renvoyer les données.
Si le nombre d'erreurs de transmission est dans les limites de la capacité de correction (erreurs non répétitives), le décodeur de canal localisera et corrigera le "0" ou "1" incorrect afin de retrouver les données transmises.



Cependant, parce que la FEC peut corriger un certain nombre de bits erronés, on peut accepter une réduction du niveau du signal reçu et le laisser chuter proche du niveau du bruit, du moment qu’on reste dans la limite des erreurs corrigibles. Cette réduction autorisée du SNR s’appelle le **gain de codage**, Cela permet de  diminuer la puissance de transmission tout en maintenant l’intégrité de l’information sur l’ensemble de la portée. 


### les  codes de Reed-Solomon
L’intérêt  de  ces  codes  RS est  que  ce  sont  des  codes  qui ont le meilleur rapport possible entres le nombre d’erreurs  qu’ils permettent de corriger par rapport à la redondance qu’ils introduisent.  
De  plus,  il  existe  des  algorithmes  de  décodage  très  efficaces.  Ils  sont  donc  très utilisés, par exemple, dans la transmission des données par ADSL ou par satellite, ou encore dans  la communication avec les sondes spatiales.

Les codes de **Reed Solomon** notés ܴܵ**RS (n, ݇k)** sont des codes de détection et de correction des erreurs.  Les messages sont divisés en blocs de ݇k octets chacun dont on a ajouté  k−n ݇ octets de redondance ou de contrôle à chaque bloc. La longueur des blocs dépend de la capacité du codeur. A la réception, le décodeur traite chaque bloc de n octets et corrige les éventuelles erreurs. A la fin de ce traitement, les données originelles seront restaurées. 

Grâce à un ajout de redondance, ces codes permettent de corriger deux types d’erreurs

 - les erreurs induisant une modification des données, ou certains bits passent de la valeur 0 à la valeur 1 et vice versa.
 - les erreurs provoquant des pertes d’informations aussi appelées effacements, lorsque des paquets d’informations sont perdus.

Un code populaire de Reed-Solomon est le **RS(255,223)** avec des symboles de 8 bits. Chaque bloc contient 255 octets, dont **223 octets de données** et **32 octets de parité**. Pour ce code :
Le décodeur peut corriger n'importe quelle **erreur de 16 symboles** dans le bloc : c'est-à-dire que les erreurs jusqu'à 16 octets n'importe où dans le bloc peuvent être corrigées automatiquement.
Étant donné une taille de symbole **s**, la longueur maximale du mot du bloc (**n**) pour un code Reed-Solomon est **n = 2s – 1**  et donc la longueur maximale d'un bloc avec des symboles de 8 bits (s=8) est de 255 octets.

Les blocs de codes Reed-Solomon peuvent être raccourcis en mettant (conceptuellement) un certain nombre de symboles de données à zéro au niveau du codeur, en ne les transmettant pas, puis en les réinsérant dans le décodeur.

Une erreur sur un octet se produit lorsqu'un bit de l'octet est erroné ou lorsque tous les bits de l'octet sont erronés. le RS(255,223) peut corriger jusqu'à 16 erreurs d'octet. Dans le pire des cas, des erreurs sur 16 bits peuvent se produire chacune dans un octet distinct, le décodeur corrige les 16 bits en erreurs sur les 16 octets. Dans le meilleur des cas, des erreurs sur 16 octets complets peuvent se produire, dans ce cas le décodeur corrige les erreurs de 16 x 8 bits. Les codes Reed-Solomon sont particulièrement bien adaptés à la correction des erreurs en rafale (où une série de bits dans le mot de code est reçue en erreur).

![Reception avec 4 octets en erreur](/programmes/testReedSolomon/Documentation/direwolf_with_4_errors.png)

### FX25 -> AX25 +FEC
**FX.25** est un protocole de transmission de données. C'est un protocole Ax.25, auquel est rajouté une couche de correction d'erreur  FEC (Forward Error Correction, basée sur le Code de Reed-Solomon.

### La trame FEC
|Préambule| tag | data | FEC | postambule |
|--|--|--|--|--|
|0x7E  | 8 octets | 32-239 octets | 16,32 ou 64 octets | 0x7E



