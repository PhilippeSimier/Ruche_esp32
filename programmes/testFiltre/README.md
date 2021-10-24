#  Les filtres RII

## Introduction
Les filtres à **réponse impulsionnelle infinie** (RII) sont utiles pour  les applications de mesure avec capteur , y compris la suppression du bruit de mesure et l'annulation de composants indésirables, tels que les interférences de ligne électrique.
Les filtres RII sont généralement choisis pour les applications où la phase linéaire n’est pas trop importante et où **la mémoire est limitée**.
La classe Filter met en œuvre un filtre biquad IIR sur un esp32,  les calculs sont  effectués sur des variable en virgule flottante.

#### Avantages du filtre RII
-   Peut être utilisé pour imiter les caractéristiques des filtres analogiques en utilisant des transformations de mappage dans le plan p-z
- Faible empreinte de mise en œuvre : nécessite moins de coefficients et de mémoire que les filtres FIR

#### Inconvénients
-   Caractéristiques de phase non linéaires.
-   Moins stables numériquement que leurs homologues RIF (réponse impulsionnelle finie), en raison des chemins de rétroaction.

## Définition

On peut écrire la fonction de transfert comme un rapport de deux polynômes.

 - Les **pôles** sont les racines du dénominateur.
 - Les **zéros** sont les  racines du numérateur
 - La **fréquence de Nyquist** est la moitié de la fréquence
   d'échantillonnage.

L’équation peut être écrite en termes d’un nombre fini de **pôles  p**  et de **zéros  q**, comme défini par l’équation de différence linéaire à coefficient constant donnée par:

y(n)=∑k=0qb(k)x(n−k)−∑k=1pa(k)y(n−k)

où  a(k)  et  b(k)  sont les coefficients polynomiaux du dénominateur et du numérateur du filtre, dont les racines sont respectivement égales aux  **pôles**  et aux  **zéros**  du filtre. Ainsi, une relation entre l’équation de différence et la transformée en z (fonction de transfert) peut donc être définie en utilisant la propriété de retard de la transformée en z telle que,

∑k=0qb(k)x(n−k)−∑k=1pa(k)y(n−k)⟷Z∑k=0qb(k)z−k1+∑k=1pa(k)z−k

Comme on le voit, la  **fonction de transfert**  est une représentation du filtre dans le domaine fréquentiel.

les **pôles** agissent sur les **données de sortie**, et les **zéros** sur les **données d’entrée**. Puisque les pôles agissent sur les données de sortie et affectent la stabilité, il est essentiel que leurs rayons **restent à l’intérieur du cercle unitaire** (c’est-à-dire <1) pour la stabilité. Les rayons des zéros sont moins critiques, car ils n’affectent pas la stabilité du filtre.

## Filtre biquad IIR

L'implémentation du filtre IIR proposée ici est dite **biquad** , car la fonction de transfert a deux pôles et deux zéros, comme illustré ci-dessous dans la figure ci dessous.
