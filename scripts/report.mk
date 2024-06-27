in_files=$(shell find . -type f ! -path './.git/*')
out_files=$(patsubst %, ../report/%, $(in_files))
out_files_dir=${dir ${out_files}}
report:clean mkdir_report_dir ${out_files} 

mkdir_report ../report: 
	mkdir -p ../report

../report/% : ./% ../report
	cp $< $@

mkdir_report_dir:
	mkdir -p ${out_files_dir}

clean:
	-rm -rf ../report