# CMPT 383 Project

using Plots # need to "using Pkg" and Pkg.add("Plots")
using PyCall


github_url = "https://github.com/search?q=created%3A2020-07-01+created%3A2020-07-31&type=Repositories"

#=
py"""
#from bs4 import BeautifulSoup # need pip install bs4
from urllib.request import Request, urlopen
import urllib.request
import re

def scrape (url):

    r_object = urllib.request.urlopen(url)
    soup = BeautifulSoup(r_object, 'html.parser')

    t = soup.findAll('a', {'class': 'filter-item'})
    count = 0
    a = []

    for text in t:
        a.append(text.text.replace(" ", '').replace("\n", '').replace(",",""))

    final = {}
    a1 = []
    a2 = []

    for el in a:
        num = int(re.search(r'\d+', el).group())
        s = re.sub(r'\d+', '', el)

        final[s] = num
        a1.append(num)
        a2.append(s)


    print(a1)
    print(a2)
    return a1,a2
"""
=#

#getVal = py"scrape"

#a = getVal(github_url)

println("Python Scraped Data:")

run(`python3 scrape.py`)

rawOutput = read(`python3 scrape.py`, String)

#println(rawOutput)
#println(rawOutput[1])
#println(rawOutput[20])
#println(Int(rawOutput[20]))

languageArr = ["JavaScript","HTML","Python","Java","CSS","Jupyter Notebook","Ruby","TypeScript","C#","PHP"] #a[1]
numArr = [22783,19483,11139,10274,5586,4769,4753,3894,3496,3264] #a[0]

total = sum(numArr)

numArr2 = convert(Array{Float64}, numArr)

ratio = numArr2./Float64(total)

p = pie(languageArr,numArr2, title = "Popularity of Programming Languages", l = 0.5)

#view = histogram(numArr, label = languageArr)

println("""Pie Chart will be saved as 'pie.png'""")
ENV["GKSwstype"]="100"
savefig("pie.png")