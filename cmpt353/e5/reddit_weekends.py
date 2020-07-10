import numpy as np
import pandas as pd
from scipy import stats
from datetime import date
import matplotlib.pyplot as plt
import sys
pd.options.mode.chained_assignment = None

OUTPUT_TEMPLATE = (
    "Initial (invalid) T-test p-value: {initial_ttest_p:.3g}\n"
    "Original data normality p-values: {initial_weekday_normality_p:.3g} {initial_weekend_normality_p:.3g}\n"
    "Original data equal-variance p-value: {initial_levene_p:.3g}\n"
    "Transformed data normality p-values: {transformed_weekday_normality_p:.3g} {transformed_weekend_normality_p:.3g}\n"
    "Transformed data equal-variance p-value: {transformed_levene_p:.3g}\n"
    "Weekly data normality p-values: {weekly_weekday_normality_p:.3g} {weekly_weekend_normality_p:.3g}\n"
    "Weekly data equal-variance p-value: {weekly_levene_p:.3g}\n"
    "Weekly T-test p-value: {weekly_ttest_p:.3g}\n"
    "Mann–Whitney U-test p-value: {utest_p:.3g}"
)


def main():
    reddit_counts = sys.argv[1]
    counts = pd.read_json(reddit_counts, lines=True) #import from file
    counts=counts[counts['date'].dt.year.isin([2012,2013])]
    counts = counts[counts['subreddit'] == 'canada'] #filter out data other than canada
    counts['day_of_week'] = counts['date'].apply(date.weekday) #get dayofweek
    weekday = counts[counts['day_of_week'].isin([0,1,2,3,4])] #seperate weekday
    weekend = counts[counts['day_of_week'].isin([5,6])] #seperate weekend

    initial_ttest_p=stats.ttest_ind(weekday['comment_count'], weekend['comment_count']) #t-test
    initial_weekday_normality_p=stats.normaltest(weekday['comment_count']) #weekday normal test
    initial_weekend_normality_p=stats.normaltest(weekend['comment_count']) #weekend normal test
    initial_levene_p=stats.levene(weekday['comment_count'],weekend['comment_count']) #equal variance test
    plt.hist(weekday['comment_count'],rwidth=0.5, color='green')
    plt.hist(weekend['comment_count'],rwidth=0.5, color='purple')

    #transform data-------------------------------------------------------------------------------------------------
    weekend['comment_count'] = np.sqrt(weekend['comment_count'])
    weekday['comment_count'] = np.sqrt(weekday['comment_count'])
    plt.hist(weekday['comment_count'],rwidth=0.5, color='green')
    plt.hist(weekend['comment_count'],rwidth=0.5, color='purple')
    transformed_weekday_normality_p=stats.normaltest(weekday['comment_count'])
    transformed_weekend_normality_p=stats.normaltest(weekend['comment_count'])
    transformed_levene_p=stats.levene(weekday['comment_count'],weekend['comment_count'])

    #Central Limit Theorem------------------------------------------------------------------------------------------
    weekday = counts[counts['day_of_week'].isin([0,1,2,3,4])] #reset weekend & weekday
    weekend = counts[counts['day_of_week'].isin([5,6])]

    weekday['week_number'] = weekday['date'].apply(date.isocalendar)
    weekend['week_number'] = weekend['date'].apply(date.isocalendar)

    def trim(x):
        x = x[0:2]
        return x

    weekday['week_number'] = weekday['week_number'].apply(trim)
    weekend['week_number'] = weekend['week_number'].apply(trim)
    weekday = weekday.groupby('week_number').aggregate('mean')
    weekend = weekend.groupby('week_number').aggregate('mean')
    weekly_weekday_normality_p=stats.normaltest(weekday['comment_count'])
    weekly_weekend_normality_p=stats.normaltest(weekend['comment_count'])
    weekly_levene_p=stats.levene(weekday['comment_count'],weekend['comment_count'])
    weekly_ttest_p=stats.ttest_ind(weekday['comment_count'],weekend['comment_count'])

    #U-test---------------------------------------------------------------------------------------------------------
    weekday = counts[counts['day_of_week'].isin([0,1,2,3,4])] #reset weekend & weekday
    weekend = counts[counts['day_of_week'].isin([5,6])]

    utest_p=stats.mannwhitneyu(weekday['comment_count'],weekend['comment_count'],alternative='two-sided')

    print(OUTPUT_TEMPLATE.format(
        initial_ttest_p=initial_ttest_p.pvalue,
        initial_weekday_normality_p=initial_weekday_normality_p.pvalue,
        initial_weekend_normality_p=initial_weekend_normality_p.pvalue,
        initial_levene_p=initial_levene_p.pvalue,
        transformed_weekday_normality_p=transformed_weekday_normality_p.pvalue,
        transformed_weekend_normality_p=transformed_weekend_normality_p.pvalue,
        transformed_levene_p=transformed_levene_p.pvalue,
        weekly_weekday_normality_p=weekly_weekday_normality_p.pvalue,
        weekly_weekend_normality_p=weekly_weekend_normality_p.pvalue,
        weekly_levene_p=weekly_levene_p.pvalue,
        weekly_ttest_p=weekly_ttest_p.pvalue,
        utest_p=utest_p.pvalue,
    ))


if __name__ == '__main__':
    main()