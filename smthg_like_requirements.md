# Requirements or smthg like this

## Notes
We are going to have two applications one for the worker, one for the master.
The master will receive the input text and show the currently best decrypted text.
He is also responsible for uploading the text in the DB, determing the size of the key and creating the tasks for the workers.
The workers should check the DB for unprocessed key intervals and process them.

We will use Postgres as db.
Qt Creator 4.1.0 based on QT 5.7.0 (C++) framework for developing in.


## Keys supported
 - small latin letters (26) 

## UI
 ### Master
  - textbox for input (encrypted text)
  - textbox for decrypted text [updated periodically]
  - button for staring operation

 ### Worker
  - textbox for input (id of the text)
  - start button
  - when no more work - notify


## Schema

### Input Text
 - id
 - text

### Tasks for workers named <id of the text>
 - id
 - from_key - interval for processing
 - to_key - interval for processing
 - best_key - the key which produced the best confidance
 - best_confidence - the best confidance achieved in this interval [index column]


## Decrypting

### Calculating confidence score
 - (Number of english words / Number of all words) * 1000