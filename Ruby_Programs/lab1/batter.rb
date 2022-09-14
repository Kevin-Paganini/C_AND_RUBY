# CS 2040
# Lab 1
# Spring 2022
# Author: Kevin Paganini


# Reads in all input from file and puts it in an array
# Params: input_file
# Returns: Batter stats array 

def get_batter_stats_array(input)
    batterstats = []
    while input != nil
        
        input = input.to_i
        batterstats = batterstats.push(input)


        input = gets
    end
    return batterstats
end 


# Gets the number of hits
# Params: batter stats array
# Returns: Number of hits  

def get_hits(batter_stats)
    hits = 0
    batter_stats.each do |n|
        if n > 0
            hits = hits + 1
        end
    end
return hits
end 

# Gets the number of at bats
# Params: batter stats array
# Returns: Number of at bats

def get_at_bats(batter_stats)
    at_bats = 0

    batter_stats.each do |n|
        if n > -1
            at_bats = at_bats + 1
        end
    end
return at_bats
end 

# Computes and prints batting average
# Params: number of hits and at bats
# Returns: Void

def compute_batting_average(hits, at_bats)
    at_bats = at_bats.to_f
    hits = hits.to_f 
    
    if at_bats != 0
        batting_avg = hits / at_bats
    else 
        batting_avg = 0     
    end

    batting_avg = batting_avg.round(3)
    batting_avg = batting_avg * 1000
    batting_avg = batting_avg.to_i

    puts 'Batting average: %d' %[batting_avg]

end


# Computes and prints average bases reached
# Params: batter stats array
# Returns: Void

def compute_average_bases(batter_stats)
    total_bases = 0
    total_appearances = batter_stats.size()
    
    batter_stats.each do |n|
        n = n.abs 
        total_bases = total_bases + n
    end

    average_bases = (total_bases.to_f/total_appearances).round(2)

    if total_appearances > 0
        puts "Average bases reached: #{average_bases}"
    else 
        puts "Average bases reached: 0.0"
    end
end 


# MAIN
input = gets # gets input from input_file
batter_stats_array = get_batter_stats_array(input)
hits = get_hits(batter_stats_array)
at_bats = get_at_bats(batter_stats_array)
compute_batting_average(hits, at_bats)
compute_average_bases(batter_stats_array)







