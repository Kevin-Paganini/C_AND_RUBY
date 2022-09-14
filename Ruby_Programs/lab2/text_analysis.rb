# CS2040
# Lab 2
# Spring 2022
# Author: Kevin Paganini


require 'set'
###############################################
# Global Variables
###############################################
$forbidden_words = Set["a", "the", "is", "are", "i", "you", "he", "she", "it", "they", "and"]
$MAX_NUM_WORDS = 8

#####################################################################
# Represents a text file being read in
# This class keeps track of the document, tokenizes it, 
# reformats it to fit output
#####################################################################
class Document

    

    attr_accessor :input, :output, :tokens, :file_name

    #####################################################################
    # Constructor
    # Actual_text (line with number)
    # Tokens (Each individual token)
    # Word_array (word object + line number)
    # output_array (formatted output)
    #####################################################################
    def initialize()
        @file_name = get_file_name()
        @input = read_input()
        @tokens = tokenize()
        @output = format_output()

    end 

    def get_file_name()
        return ARGV[0]
    end

    #####################################################################
    # Formats text output
    #####################################################################
    def format_output()
        
        actual_words = @tokens.map {|x| x.word}
        output = []
        grouped_tokens = actual_words.each_slice($MAX_NUM_WORDS).to_a
        grouped_tokens.each {|x| output << x.join(" ")}
        return output.join("\n")
        
    end  
        
 
        
   
    #####################################################################
    # Seperates lines into individual tokens 
    #####################################################################
    def tokenize()
        token_list = []
        @input.each do |line|
        tokens_line = line.line.split(" ") # splitting line into individual words
        tokens_line.each {|x| token_list << Word.new(x, line.line_number)} # storing word objects in list
            
        end 
        
        return token_list
       
    end 

    #####################################################################
    # Takes input from ARGF
    # Writes line to array and keeps track of line number
    # WHy does the array not print with brackets?
    #####################################################################
    def read_input()
        line_number = 0
        input_array_of_words = []
        ARGF.each_line do |line|
            input_array_of_words << Line.new(line_number +=1, line)
        end
        
        return input_array_of_words
    end
    
end 



#####################################################################
# Word class 
# Stores word as well as line it was found on
#####################################################################

class Word

    attr_accessor :word, :line 

    #####################################################################
    # Constructor
    # Params: Word, line number
    #####################################################################
    def initialize(word, line)
        @word = word
        @line = line
    end 

    #####################################################################
    # formatting the word to not have certain punctuation characters
    # return new Word object
    #####################################################################
    def format()
        return Word.new(@word.strip.downcase.gsub(/[;:,.]/, ''), line)
    end
end

#####################################################################
# Line class 
# Stores entire line of words as well as lines line number
#####################################################################
class Line

    attr_accessor :line_number, :line

    #####################################################################
    # Constructor
    # Params: Line, line number
    #####################################################################
    def initialize(line_number, line)
        @line = line
        @line_number = line_number
    end 

end

#####################################################################
# Bigram class
# Makes pairs of words 
#####################################################################
class Bigram 

    attr_accessor :first_word, :second_word, :phrase

    #####################################################################
    # Constructor
    # Params: First word, second word
    # Attributes: First word, second word, combination of two (First word + second word)
    #####################################################################
    def initialize(first_word, second_word)
        @first_word = first_word
        @second_word = second_word
        @phrase = display_bigram
    
    end 
    #####################################################################
    # Put it in phrase form
    # First word + second word
    #####################################################################
    def display_bigram()

        return @first_word.word + " " + @second_word.word
    end


    #####################################################################
    # checks if two Bigrams have same instance values
    # same first word and same second word
    #####################################################################
    def are_we_equal(other)
        return self.first_word.word == other.first_word.word && self.second_word.word == other.second_word.word
    end 


end 




#####################################################################
# Analysis Class
# Does analysis of the document 
#####################################################################
class Analysis

    attr_accessor :num_lines, :document, :forbidden_words, :no_punctuation, :no_punc_or_forbidden_words, :bigrams, :duplicate_bigrams

    #####################################################################
    # Constructor
    # Params: Document (Which document to analyse)
    # Attributes: num_lines (number of lines in document)\
    #             no_punctuation (tokens of document without punctuation)
    #             no_punc_or_forbidden_words (removing forbidden words from no punctuation)
    #             bigrams (list of bigrams) 
    #             duplicate_bigrams (Hash of duplicate bigrams)
    #####################################################################
    def initialize(document)
        @document = document
        @num_lines = get_num_lines()
        @no_punctuation = removing_punctuation()
        @no_punc_or_forbidden_words = remove_forbidden_words()
        @bigrams = make_bigrams()
        @duplicate_bigrams = duplicate_bigrams()
        
    end
    #####################################################################
    # Gets the number of lines in output 
    #####################################################################
    def get_num_lines()
        output_lines = @document.output.split("\n")

        return "Output line count: %d" %output_lines.length

    end 
    #####################################################################
    # Removing punctuation from token list of document
    # Returns: Token list with clean (no punctuation) tokens
    #####################################################################
    def removing_punctuation()
        no_punctuation = []
        @document.tokens.each {|x| no_punctuation << x.format}
        
        return no_punctuation
    end 
    #####################################################################
    # Remove forbidden words from no punctuation list
    # Returns: token list without punctuation and forbidden words
    #####################################################################
    def remove_forbidden_words()
        
        no_forbidden_words = @no_punctuation.select {|x| !$forbidden_words.include?(x.word)}

        
        
        return no_forbidden_words
    end 

    #####################################################################
    # Make bigrams of entire no punctuation and forbidden word list
    # Returns: List of bigrams of entire document excluding puncs and forbidden words
    #####################################################################
    def make_bigrams()
        bigram_list = []
        word_pairings = no_punc_or_forbidden_words.each_cons(2).to_a
        word_pairings.each {|x| bigram_list << Bigram.new(x[0], x[1])}
        return bigram_list
    end 
    #####################################################################
    # Find and sort duplicate bigrams
    # Returns: Hash of sorted duplicate bigrams
    #####################################################################
    def duplicate_bigrams()
        #check each element in bigram list against every other element in bigram list
        # store which bigrams are repeated
        # store which lines the bigram happens in 
        bigram_hash = Hash.new {|h,k| h[k] = []}
        @bigrams.each {|x| bigram_hash[x.phrase] << x}
        repeated_bigrams = bigram_hash.select {|key, value| value.length > 1}
        
        
        return repeated_bigrams.sort_by {|key, value| [-value.length, key]}
    end 






end 

#####################################################################
# Class Output_Printer
# Prints desired output
#####################################################################
class Output_Printer 

    
    #####################################################################
    # Constructor
    # Params: Document (Which document to analyse and print output)
    #         Output_string (String version)
    #####################################################################
    def initialize(document)
        @document = document
        @output_string = output_string()
    end 

    #####################################################################
    # Make output string
    #####################################################################
    def output_string()
        analysis = Analysis.new(@document)
        
        if(@document.output != "")
            output_string = @document.output + "\n"
        else
            output_string = ""
        end 
        output_string += "---------- analysis ----------" + "\n"
        output_string += analysis.num_lines + "\n"
        output_string += "Repeated phrase count: %d" %analysis.duplicate_bigrams.length + "\n"
        output_string += "Repeated phrases:" + "\n"
        analysis.duplicate_bigrams.each {|key, value| output_string += key + ": " + value.map {|bigram| bigram.first_word.line}.join(", ") + "\n"}
        return output_string
    end

    #####################################################################
    # Write output string to file 
    #####################################################################
    def write_output()
        File.open("#{@document.file_name.gsub(".txt", "")}.out", "w") {|f| f.write @output_string}
    end

end 

#####################################################################
# Main function 
#####################################################################
class Main
    if __FILE__ == $0
        puts Output_Printer.new(Document.new).output_string()
        
        
        

        
    end
end
