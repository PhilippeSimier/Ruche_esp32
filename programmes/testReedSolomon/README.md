# FEC 

## 1- Présentation

D'inévitables erreurs de transmission  se  produisent   et  il  faut  parer  a  ce  phénomène.  Une  des  réponses possibles réside dans les **codes correcteurs d’erreurs**.
Le mode d’action de ces codes correcteurs d’erreurs repose sur le principe  suivant : au lieu d’envoyer les données à transmettre directement dans le canal  de transmission, celles-ci sont préalablement encodées, c’est-à-dire qu’**il leur  est adjoint une petite quantité d’information supplémentaire,** appelée redondance, de façon à ce qu’il soit possible, à la réception de la communication,  de  détecter  d’ éventuelles  erreurs  de  transmission  et  de les corriger, autrement dit retrouver les données qui ont  été altérées au cours  de leur transfert.

### les  codes de Reed-Solomon
L’intérêt  de  ces  codes  est  que  ce  sont  des  codes  de  paramètres  optimaux c’est-à-dire qu’ils ont le meilleur rapport possible entres le nombre d’erreurs  qu’ils permettent de corriger par rapport à la redondance qu’ils introduisent.  
De  plus,  il  existe  des  algorithmes  de  décodage  très  efficaces.  Ils  sont  donc  
très utilisés, par exemple, dans la transmission des données par ADSL ou par satellite, ou encore dans  la communication avec les sondes spatiales.

### FX25 -> AX25 +FEC
**FX.25** est un protocole de transmission de données. C'est un protocole Ax.25, auquel est rajouté une couche de correction d'erreur  FEC (Forward Error Correction, basée sur le Code de Reed-Solomon.

### La trame FEC
|Préambule| tag | data | FEC | postambule |
|--|--|--|--|--|
|0x7E  | 8 octets | 32-239 octets | 16,32 ou 64 octets | 0x7E



