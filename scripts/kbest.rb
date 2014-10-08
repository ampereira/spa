# !/bin/ruby

require 'date'
require 'socket'

class Kbest

# report is either csv or verbose
	def initialize(th,_k,min,max,script,file,mode)
		@threshold = 1 + th.to_f
		@k = _k.to_i
		@min_runs = min.to_i
		@max_runs = max.to_i
		@filename = file
		@report = mode
		@runscript = script
	end

	def runapp
		cmd = "./" + @runscript
		system(cmd)
	end

# Note: the current best value also counts for the
#       k best 
# validated
	def check(best, results)
		mag = best * @threshold
		amount = 0

		results.each do |value|
			if value <= mag
				amount += 1
			end
		end

		if amount < @k
			return false
		else
			return true
		end
	end

# validated
	def print_results_verbose(best, flag)
		new_file = @filename + ".txt"
		date = DateTime.now.to_s
		host = Socket.gethostname

		file = File.open(new_file, "a")

		string =  "**********************************\n"
		string << "******* Measurement Report *******\n"
		string << "**********************************\n\n"
		string << "#{date}\t#{host}\n\n"

		if flag
			string << "\t#{best}\tvalid\n"
		else
			string << "\t#{best}\ttimeout\n"
		end
			
		file.write(string)
		file.close
	end

	def print_results_csv(best)
		new_file = @filename + ".csv"

		if File.exists? new_file
			file = File.open(new_file, "a")
			string = ",#{best}"
		else
			file = File.open(new_file, "a")
			string = "#{best}"
		end
			
		file.write(string)
		file.close
	end

	def print_results(best,flag)
		if @report.downcase.eql? "csv"
			print_results_csv(best)
		else
			print_results_verbose(best,flag)
		end
	end

	def run
		i = 1
		best = 1000000000000
		results = Array.new
		flag = false

		while i <= @max_runs and !flag do
			runapp
			_filename = "minimum.csv"
			file = File.new(_filename,"r")

			while (time = file.gets) do
				a = Float(time)

				if a < best
					best = a
				end

				results << a
			end

# is it in the k best?
			if i >= @min_runs
				flag = check(best, results)
			end

			i += 1
			File.delete(_filename)
		end
# always prints the best result even if it has
# no k values within the threshold, in case of
# timeout
		print_results(best, flag)
	end
end

# Run the scritp!
if __FILE__ == $0
	if ARGV.size < 7
		puts "Not enough arguments"
	else
		kb = Kbest.new(ARGV[0],ARGV[1],ARGV[2],ARGV[3],ARGV[4],ARGV[5],ARGV[6])
		kb.run
	end
end

