# RT1064 Reference Source

This directory is a direct source import of the SJTU-AuTop RT1064 project
layout used as the algorithm reference.

Source:

```text
GitHub: https://github.com/SJTU-AuTop/RT1064-Code.git
Local:  /mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code
Commit: 4038f81ad85f915adc988f3791887b1c823ae350
Log:    4038f81 Merge pull request #6 from Calvariaa/master
```

Imported paths:

```text
Project/CODE/
Project/USER/inc/
Project/USER/src/
```

Deliberately not imported:

```text
Project/**/.ace-tool/
```

Those are local tool index caches, not source code.

Porting rule:

```text
Keep Project/CODE and Project/USER source layout recognizable.
Do not rewrite the reference algorithm into runtime_t/rt->track style.
Use a separate port layer for camera, IPM tables, GPIO, encoder, motor,
display/report, time, and differential-drive output.
```
