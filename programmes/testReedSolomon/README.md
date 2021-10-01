# RS -FEC 

## 1- **Correction d’erreur sans voie de retour (FEC)**

Comme nous le savons, les signaux radios peuvent parfois se détériorer au cours de la transmission en raison de certains facteurs et cela peut conduire à une erreur de décodage du côté récepteur, qui peut confondre le signal "1" avec le signal "0", ou le signal "0" avec le signal "1". D'inévitables erreurs de décodage  se  produisent   et  il  faut  parer  a  ce  phénomène.  Une  des  réponses possibles réside dans les **codes correcteurs d’erreurs**.
La correction d’erreur sans voie de retour est un procédé dans lequel les résultats des algorithmes sont envoyés comme information supplémentaire avec les données. En répétant les mêmes algorithmes à l’autre extrémité, le récepteur a la possibilité de détecter les erreurs au bit près et de les corriger (erreurs corrigibles) sans devoir demander à renvoyer les données.
Si le nombre d'erreurs de transmission est dans les limites de la capacité de correction (erreurs non répétitives), le décodeur de canal localisera et corrigera le "0" ou "1" incorrect afin de retrouver les données transmises.



Cependant, parce que la FEC peut corriger un certain nombre de bits erronés, on peut accepter une réduction du niveau du signal reçu et le laisser chuter proche du niveau du bruit, du moment qu’on reste dans la limite des erreurs corrigibles. Cette réduction autorisée du SNR s’appelle le gain de codage, Cela permet de  diminuer la puissance de transmission tout en maintenant l’intégrité de l’information sur l’ensemble de la portée. 


### les  codes de Reed-Solomon
L’intérêt  de  ces  codes  est  que  ce  sont  des  codes  de  paramètres  optimaux c’est-à-dire qu’ils ont le meilleur rapport possible entres le nombre d’erreurs  qu’ils permettent de corriger par rapport à la redondance qu’ils introduisent.  
De  plus,  il  existe  des  algorithmes  de  décodage  très  efficaces.  Ils  sont  donc  très utilisés, par exemple, dans la transmission des données par ADSL ou par satellite, ou encore dans  la communication avec les sondes spatiales.

### FX25 -> AX25 +FEC
**FX.25** est un protocole de transmission de données. C'est un protocole Ax.25, auquel est rajouté une couche de correction d'erreur  FEC (Forward Error Correction, basée sur le Code de Reed-Solomon.

### La trame FEC
|Préambule| tag | data | FEC | postambule |
|--|--|--|--|--|
|0x7E  | 8 octets | 32-239 octets | 16,32 ou 64 octets | 0x7E



