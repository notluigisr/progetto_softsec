# Confronto tra Metodi Tradizionali e Basati su LLM per la Rilevazione delle Vulnerabilità nel Codice Sorgente

## Descrizione del Progetto

Questo progetto ha lo scopo di confrontare l'efficacia e l'efficienza dei metodi tradizionali di rilevazione delle vulnerabilità (cppcheck, flawfinder, clang) con metodi basati su Large Language Models (LLM) come T5 e CodeBERT. L'obiettivo è valutare le prestazioni di questi strumenti nell'identificazione di vulnerabilità nel codice sorgente, analizzando metriche come precisione, recall, F1-score, tempo di esecuzione e utilizzo delle risorse.

Il dataset DiverseVul è disponibile a questo link https://drive.google.com/file/d/12IWKhmLhq7qn5B_iXgn5YerOQtkH-6RG/view?usp=sharing
## Struttura del Repository

- `datasets/`: Contiene i dataset utilizzati per l'analisi e il confronto.
  - `juliet/`: Juliet dataset con analisi.
  - `diverseVul/`: DiverseVul dataset con analisi.

- `traditional_methods/`: Contiene gli script e i file di configurazione per l'analisi con strumenti tradizionali.
  - `cppcheck/`: Script e output di cppcheck.
  - `flawfinder/`: Script e output di flawfinder.
  - `clang/`: Script e output di clang.

- `llm_methods/`: Contiene i quaderni Jupyter e i modelli per l'analisi con LLM.
  - `T5/`: Quaderni per l'addestramento e l'uso del modello T5.
  - `CodeBERT/`: Quaderni per l'addestramento e l'uso del modello CodeBERT.

- `README.md`: Questo file, con la descrizione del progetto.
