git-update:
	git fetch origin
	git switch main
	git pull
	cd modules
	git submodule update --remote
