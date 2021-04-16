# Arhitectura Sistemelor de Calcul - Tema 1 - Marketplace, Martie 2021

## Sistemul de testare si testele temei

Infrastructura de testare poate fi folosită pentu a genera fisiere de test în format JSON:

`` python test_generator h``

## Descrierea conținutului fișierului de intrare:

### Marketplace Key (“marketplace”):

Obiect ce conține un singur câmp, reprezentat printr-o mapare dintre un string “queue_size” si un int, acesta reprezentand dimensiunea maximă a cozii în care poate scrie producatorul.

**Exemplu**:
```json
    “marketplace”: {
        “queue_size”: 8
    }
```

### Products Key (“products”):
Vor exista mai multe obiecte ce vor constitui produsele care vor putea fi cumpărate de către clienți.  Fiecare dintre aceste obiecte va fi reprezentat prin intermediul unei mapări dintre un string “id” și o descriere a produsului. Descrierea produsului în cauză va fi constituită din elementele sale specifice, în funcție de tipul produsului pus la dispoziție. În urma rezolvării acestei descrieri, pentru fiecare mapare se va obține un obiect de tip Produs care va intra în lista de produse pe care Marketplace-ul o va pune la dispoziție clienților săi. 


**Exemplu**: 
	Produsul ``Coffee(name=”Arabica”, price=10, acidity=5.1, roast_level=medium)`` va fi descris prin intermediul următoarei configurări:
```json
    “id1”: {
	    “prod_type”: “Coffee”,
	    “name”: “Arabica”,
	    “price”: 10,
	    “acidity”: 5.1,
	    “roast_level”: “medium”
    }
```


### Producer Key (“producers”):

Lista de obiecte -- fiecare obiect va contine următoarele mapări:


- “name”: numele producatorului
- “products”: lista de liste -- fiecare lista interioară va contine:
    - id-ul produsului pe care îl va furniza
    - cantitatea de produse de tipul respectiv furnizată
    - timpul de așteptare pentru producerea fiecărui produs
- “sleep_on_publish_false”: timpul de așteptare al producătorului în cazul în care acestuia nu îi mai este permisă furnizarea altor produse

**Exemplu**:
```json
	{
	    “name”: “prod1”,
		“products”: [
	        [“id1”, 2, 0.1],
	        [“id2”, 1, 0.3]
        ],
        “republish_wait_time”: 0.2
    }
```

Exemplul de mai sus descrie un singur producător cu numele “prod1”. Produsele pe care acesta le va furniza au id-urile id1, respectiv id2 (id-uri ce vor fi mapate la obiecte de tip Cafea / Ceai). Cantitatea produselor care au id-ul “id1” cu care va aproviziona producătorul “prod1” Marketplace-ul, este 2, pentru cele cu id-ul “id2” fiind 1. Fiecare produs va avea propriul timp de procesare:

- produs “id1” -> 0.1 secunde
- produs “id2” -> 0.3 secunde


### Consumers Key (“consumers”):

Lista de obiecte -- fiecare obiect contine următoarele mapări:


- “name”: numele cumparatorului
- “retry_wait_time”: timpul de așteptare al consumatorului în cazul în care produsul pe care îl dorește nu este disponibil
- “carts”: lista de liste -- fiecare dintre listele interne va conține tipul de operație ce va fie efectuată de către consumator:
- “type” -- tipul operației
- “prod” -- id-ul produsului
- “quantity” -- cantitatea produsului

**Exemplu**:
```json
	{
		“name”: “cons1”,
		“sleep_on_add_false”: 0.1,
		“carts”: [
		    [
                { 
                    “type”: “add”,
                    “prod”: “id1”,
                    “quantity”: 2
                },
                {
			        “type”: “remove”,
			        “prod”: “id1”,
			        “quantity”: “1”
                }
            ],
			[
                {
                    “type”: “add”,
                    “prod”: “id2”,
                    “quantity”: 3
                }
             ],
    }
```

Exemplul de mai sus descrie un singur consumator cu numele “cons1”. Operațiile pe care acesta le va efectua asupra coșului său de cumpărături sunt următoarele:

- va adăuga în coș doua produse cu id-ul “id1”
- va elimina din cos un produs cu id-ul “id1”
- va adăuga în coș trei produse cu id-ul “id2”
