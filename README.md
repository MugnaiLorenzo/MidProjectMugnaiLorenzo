# MidProjectMugnaiLorenzo

### 📌 Descrizione
Questo progetto implementa un'analisi di **n-grammi** (bigrammi e trigrammi) utilizzando due strutture dati diverse:
- **AoS (Array of Structures)**
- **SoA (Structure of Arrays)**

Le implementazioni sono disponibili sia in modalità **sequenziale** che **parallela**, con il supporto alla **vettorizzazione** via **SIMD**.

Il progetto include anche un **benchmark** per misurare i tempi di esecuzione e il **speedup** delle varie implementazioni.

---

## 🛠️ Installazione e Setup

### 1️⃣ Prerequisiti
Assicurati di avere installato:
- **CMake** (≥ 3.27)
- **GCC/Clang con supporto OpenMP**
- **Gnuplot** (per la generazione dei grafici)

### 2️⃣ Compilazione
Esegui i seguenti comandi nella root del progetto:

```bash
mkdir build && cd build
cmake ..
make
```

### 3️⃣ Esecuzione
Dopo la compilazione, esegui:

```bash
./MidProjectMugnaiLorenzo
```

---

## ⚙️ Struttura del Progetto
```
📂 MidProjectMugnaiLorenzo
├── 📂 SoA
│   ├── ParallelSoA.cpp
│   ├── ParallelSoA.h
│   ├── SequentialSoA.cpp
│   ├── SequentialSoA.h
├── 📂 AoS
│   ├── ParallelAoS.cpp
│   ├── ParallelAoS.h
│   ├── SequentialAoS.cpp
│   ├── SequentialAoS.h
│   ├── Ngram.cpp
│   ├── Ngram.h
├── 📂 include
│   ├── gnuplot.h
│   ├── Benchmark.cpp
│   ├── Benchmark.h
├── 📂 Testi (Dataset di testi per l'analisi)
├── 📂 Image (Output dei grafici generati)
├── main.cpp
├── CMakeLists.txt
└── README.md
```

---

## 🚀 Funzionamento
### 🔹 **Caricamento dei Testi**
I file di testo vengono caricati dalla cartella `Testi/`, con un ciclo su **29 libri** disponibili.

### 🔹 **Esecuzione dell'Analisi**
Per ogni configurazione:
- **Sequenziale AoS**
- **Parallelo AoS (con vari thread)**
- **Sequenziale SoA**
- **Parallelo SoA (con vari thread)**
- **Parallelo SoA con Vettorizzazione**

vengono calcolati i tempi di esecuzione e stampati i risultati.

### 🔹 **Benchmark e Speedup**
Il modulo `Benchmark` salva i tempi e genera **grafici dei tempi di esecuzione** e **grafici del speedup** utilizzando **Gnuplot**.

---

## 📊 Output e Grafici
Il programma genera grafici salvati in `Image/Plot/`, tra cui:
- **Esecuzione Sequenziale vs Parallela**
- **Speedup delle versioni parallele**
- **Distribuzione degli n-grammi più frequenti**

---

## 📌 Autore
**Lorenzo Mugnai** - _MidProject_
