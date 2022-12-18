valgrind --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --verbose \
  --error-exitcode=1 \
  --log-file="$(dirname "$0")/../artifacts/valgrind.log" \
  "$(dirname "$0")/../artifacts/c-string-reader" -t "$(dirname "$0")/input.txt" >"$(dirname "$0")/../artifacts/c-string-reader.log"

status=$?

echo "valgrind.log:"
cat "$(dirname "$0")/../artifacts/valgrind.log"

echo "c-string-reader.log:"
cat "$(dirname "$0")/../artifacts/c-string-reader.log"

echo ""
echo "summary:"
if [ "$status" -eq 1 ]; then
  echo "valgrind failed"
  exit 1
else
  echo "valgrind passed"
  exit 0
fi