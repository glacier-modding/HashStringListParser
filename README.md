# HashListStringParser
## Usage
`HashListStringParser.exe hashlist_filename.txt`

This will create a `duplicates.txt` and `master_hash_to_string_list.txt` file.

`duplicates.txt` will contain something like this:
```
00B6993D9DBF2147.ALOC, has duplicate: 00B6993D9DBF2147.ALOC,[assembly:/_pro/environment/geometry/props/furniture/shelving_unit_wooden_modern_a.wl2?/wall_japanese_modern_a.prim].pc_coll
```

`master_hash_to_string_list.txt` will be a copy of the hash list with your newely merged hashes.