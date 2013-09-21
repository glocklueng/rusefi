bash -c "date" > time.before
rm -rf .dep/
make
bash -c "date" > time.after