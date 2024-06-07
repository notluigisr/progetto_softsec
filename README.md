# Confronto tra Metodi Tradizionali e Basati su LLM per la Rilevazione delle Vulnerabilità nel Codice Sorgente

## Descrizione del Progetto

Questo progetto ha lo scopo di confrontare l'efficacia e l'efficienza dei metodi tradizionali di rilevazione delle vulnerabilità (cppcheck, flawfinder, clang) con metodi basati su Large Language Models (LLM) come T5 e CodeBERT. L'obiettivo è valutare le prestazioni di questi strumenti nell'identificazione di vulnerabilità nel codice sorgente, analizzando metriche come precisione, recall, F1-score, tempo di esecuzione e utilizzo delle risorse.

Il dataset DiverseVul è disponibile a questo link https://drive.google.com/file/d/12IWKhmLhq7qn5B_iXgn5YerOQtkH-6RG/view?usp=sharing
## Struttura del Repository

- `datasets/`: Contiene i dataset utilizzati per l'analisi e il confronto.

- `traditional_methods/`: Contiene gli script, notebook e i file di configurazione per l'analisi con strumenti tradizionali.

- `llm_methods/`: Contiene i notebook Jupyter e i modelli per l'analisi con LLM.

- `abstract_syntax_tree/`: Contiene i notebook Jupyter per l'estrazione e analisi del codice sotto forma di AST.

- `resembled_learning/`: Contiene i approcci di resembled learning dei modelli addestrati.

- `comparison/`: Contiene i risultati dei tool e modelli con il notebook in cui viene effettuata una comparazione.

- `README.md`: Questo file, con la descrizione del progetto.