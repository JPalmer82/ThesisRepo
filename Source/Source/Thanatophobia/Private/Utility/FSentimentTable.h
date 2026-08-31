// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "FSentimentTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSentimentTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SentimentTable)
	float Random;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SentimentTable)
	FString Word;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SentimentTable)
	FString Sentiment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SentimentTable)
	FString Category;
};

UCLASS()
class UFSentimentTable : public UStruct
{
	GENERATED_BODY()
	
};
