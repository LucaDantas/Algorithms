# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
# Give the code to be hashed in stdin
cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum |cut -c-6
