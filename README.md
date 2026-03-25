<div align="center">

# 🎥 Cinema manager

Progetto per il corso di Programmazione ad Oggetti con valutazione 31/30.

</div>

---

## 📋 Abstract

Il progetto presenta il concetto di una libreria multimediale progettata come gestionale per una catena di cinema. I media sono rappresentati da ciò che si può trovare sul grande schermo dei cinema: i film, i trailer e le inserzioni pubblicitarie. Inoltre sono inclusi tra i media anche i podcast e le loro puntate che la catena di cinema distribuisce sui propri canali. Per ogni cinema, l'applicazione consente di visualizzare i media, modificarne le caratteristiche, cercarli (attraverso titolo o autore) e cancellarli.

L'idea che sta alla base del progetto si ispira alla modalità con cui i principali cinema programmano la proiezione e distribuzione dei propri contenuti. Per esempio, recandosi sul sito di __The Space Cinema__ si troveranno difficilmente gli orari di programmazione di film oltre la settimana corrente perchè spesso la loro proiezione futura dipende dalle vendite passate (salvo casi particolari).

Il gestionale rende semplice la supervisione e la scelta di estendere la programmazione alle settimane o mesi successivi attraverso anche la semplicità di utilizzo e la grafica moderna. Le modalità con cui gli incassi vengono calcolati o le date vengono estese per ogni tipologia di contenuto sfrutta il polimorfismo della gerarchia dei media.

---

## 🎬 Funzionalità

<table>
  <tr>
    <td width="30%" valign="top">
      <h3>1) Gestisci la tua catena di cinema!</h3>
      <p>Puoi aggiungere, modificare ed eliminare i tuoi cinema</p>
    </td>
    <td width="70%" valign="top">
      <img src="https://github.com/user-attachments/assets/bc4ab7b7-43c4-43f0-8e70-9f0770140a89" width="100%">
    </td>
  </tr>
  <tr>
    <td width="30%" valign="top">
      <h3>2) Gestisci i tuoi media e organizza la programmazione</h3>
      <p>Scegli quando distribuire in sala i tuoi film, trailer, inserzioni ma anche podcast e puntate!</p>
      <p>Potrai visualizzare quelli che si trovano in sala o on-air oppure uno storico delle programmazioni passate</p>
    </td>
    <td width="70%" valign="top">
      <img src="https://github.com/user-attachments/assets/75048512-9c44-403f-a534-385fe94ba96a" width="100%">
      <img src="https://github.com/user-attachments/assets/119bd9b8-968c-412b-996a-a2351f6b38a4" width="100%">
    </td>
  </tr>
  <tr>
    <td width="30%" valign="top">
      <h3>3) Visualizza un media e prolunga la sua durata in sala</h3>
      <p>Ogni media ha una sua visualizzazione personalizzata</p>
      <p>Scegli se estendere la sua programmazione con un comodo pulsante</p>
      <p>Modifica i suoi dettagli quando vuoi</p>
    </td>
    <td width="70%" valign="top">
      <img src="https://github.com/user-attachments/assets/2cbcdecc-b06a-4696-ab47-8209a6b9b5b5" width="100%">
    </td>
  </tr>
  <tr>
    <td width="30%" valign="top">
      <h3>4) Aggiungi un nuovo media</h3>
      <p>Ogni tipologia di media ha un'immagine di default</p>
      <p>Inserisci i dettagli di base e quelli più specifici</p>
      <p>Modifica i suoi dettagli quando vuoi</p>
      <p>Hai fatto un errore? puoi eliminare il media quando vuoi</p>
    </td>
    <td width="70%" valign="top">
      <img src="https://github.com/user-attachments/assets/e17639f7-9155-4559-8012-7211c685b731" width="100%">
    </td>
  </tr>
  <tr>
    <td width="30%" valign="top">
      <h3>5) Fai il backup di intere sessioni di cinema in file xml, puoi importarle quando vuoi</h3>
      <p>Puoi esportare cinema in xml e importarli nuovamente: comodo backup o per condividere cinema</p>
    </td>
    <td width="70%" valign="top">
      <img src="https://github.com/user-attachments/assets/c8457c95-7b89-47b2-9ea4-211bddc61f93" width="100%">
    </td>
  </tr>
  <tr>
    <td width="30%" valign="top">
      <h3>6) Importa ed esporta film in xml per aggiungerli ad altri cinema</h3>
      <p>Puoi esportare cinema in xml e importarli nuovamente: comodo backup o per condividere cinema</p>
    </td>
    <td width="70%" valign="top">
      <img src="https://github.com/user-attachments/assets/52084e62-3814-4c07-b8e5-c5d06ab8b181" width="100%">
    </td>
  </tr>
</table>

---

## 🔍 Scopri di più

### Persistenza dei dati e gestione memoria

La persistenza dei dati è gestita tramite il formato strutturato **Json**. All'apertura dell'applicazione, essa carica automaticamente il file `media.json` che si trova all'interno della cartella `Json_XML` nella root del progetto, altrimenti il file viene creato senza contenuti.

Se il file contiene già dei `Cinema` con i relativi media, gli oggetti `Cinema` (costituiti da nome e path dell'immagine) vengono costruiti e resi disponibili all'apertura dell'applicazione. Una volta aperto un cinema, i suoi media vengono letti da `s_jsonManager` e convertiti in oggetti `Media*` tramite la funzione `loadMedia(QList<Media*>&, const QString&)`. Infine gli oggetti vengono raccolti in una `QList` temporanea `s_MediaListOfCinema`. In alternativa, l'utente può creare un nuovo cinema (che verrà salvato in `media.json`) e successivamente aggiungervi i media desiderati.

I media vengono quindi allocati in memoria solo quando si entra all'interno di un cinema e all'uscita vengono deallocati. Queste considerazioni sono state fatte per ottimizzare l'uso della memoria. Il processo rinizia ad ogni cambio cinema.
