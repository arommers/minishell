/*
	Possible workflow for collaborating on Github.

	The set up would be one main (origen) branch and a separate branch for each of us.
	- Making a new branch
		type git branch "branch name".
	- Moving to the specific branch
		* git checkout "branch name".
		* git checkout master (to move back to the main branch)
	- Merging changes remotely
		* add, commit from branch to master
		* move to main branch
		* git merch "branch name" (to add changes made to the main branch)
		* push to add to the remote repository
	- When starting git pull first
		* push changes to own branch
		* move to branch and start working on it
*/