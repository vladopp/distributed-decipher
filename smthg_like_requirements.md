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

### Input Text (table texts)
 - id
 - encr_text
 - decr_text

### Tasks for workers named <id of the text> (table tasks)
 - id
 - from_key - interval for processing
 - to_key - interval for processing
 - text_id - id of the text that this task is for
 - processed - boolean flag to indicate if this task has been started yet

### Probable keys (table solutions)
 - id
 - key - the key that gave this result
 - confidence - the probability that this is THE KEY
 - text_id - id of the text that this solution is for
 - result - the result of decyphering the given encrypted text with this key


Here is how the DB schema looks like.

solutions      texts          tasks
---------      -----          -----
id         --> id      <---   id        
key        |   encr_text  |   from_key
confidence |   decr_text  |   to_key
text_id  ---              --- text_id
result	                      processed

This schema suggests the following workflow for the application:
1. User enters a text to decrypt.
2. The master node takes the text and adds an entry for it in the "texts" table (if such doesn't exist yet, otherwise returns the already decrypted text). Then, divides the task of finding the optimal key into subtasks and adds them as entries into the "tasks" table.
3. Slaves figure out that there are new tasks to execute (by querying the "tasks" table frequently) and start picking unprocessed tasks.
4. When finished, each slave adds exactly one entry to the "solutions" table with their findings.
5. The master figures out that all tasks for the given text have been completed (by frequently querying the "tasks" table), and takes the solution (from the "solutions" table) that has the highest confidence for the given text_id. The master then prints the corresponding result to the user and saves it into the DB, so that we don't decrypt the same text twice.


## Decrypting

### Calculating confidence score
 - (Number of english words / Number of all words) * 1000
