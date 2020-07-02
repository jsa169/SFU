import sys
import numpy as np
import pandas as pd
from scipy import stats

OUTPUT_TEMPLATE = (
    '"Did more/less users use the search feature?" p-value: {more_users_p:.3g}\n'
    '"Did users search more/less?" p-value: {more_searches_p:.3g}\n'
    '"Did more/less instructors use the search feature?" p-value: {more_instr_p:.3g}\n'
    '"Did instructors search more/less?" p-value: {more_instr_searches_p:.3g}'
)


def main():
    searchdata_file = sys.argv[1]

    searches = pd.read_json(searchdata_file,orient='records',lines=True)
    searches['searched_at_least_once'] = (searches['search_count'] != 0)

    odd_treatment = searches[searches['uid']%2 == 1]
    even_control = searches[searches['uid']%2 == 0]

    contingency = ([odd_treatment['searched_at_least_once'].value_counts().loc[True],odd_treatment['searched_at_least_once'].value_counts().loc[False]],
               [even_control['searched_at_least_once'].value_counts().loc[True],even_control['searched_at_least_once'].value_counts().loc[False]])
    _, more_users_p, _, _, = stats.chi2_contingency(contingency)
    
    more_searches_p = stats.mannwhitneyu(odd_treatment['search_count'], even_control['search_count'])

    instructors = searches[searches['is_instructor'] == True]

    odd_treatment = instructors[instructors['uid']%2 == 1]
    even_control = instructors[instructors['uid']%2 == 0]

    contingency = ([odd_treatment['searched_at_least_once'].value_counts().loc[True],odd_treatment['searched_at_least_once'].value_counts().loc[False]],
               [even_control['searched_at_least_once'].value_counts().loc[True],even_control['searched_at_least_once'].value_counts().loc[False]])
    _, more_instr_p, _, _, = stats.chi2_contingency(contingency)

    more_instr_searches_p = stats.mannwhitneyu(odd_treatment['search_count'], even_control['search_count'])
    
    # Output
    print(OUTPUT_TEMPLATE.format(
        more_users_p=more_users_p,
        more_searches_p=more_searches_p.pvalue,
        more_instr_p=more_instr_p,
        more_instr_searches_p=more_instr_searches_p.pvalue,
    ))


if __name__ == '__main__':
    main()
